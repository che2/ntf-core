// Copyright 2020-2023 Bloomberg Finance L.P.
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_NTCS_PROACTORDETACHCONTEXT
#define INCLUDED_NTCS_PROACTORDETACHCONTEXT

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

#include <ntci_proactorsocket.h>
#include <ntcs_dispatch.h>
#include <ntsa_error.h>
#include <bsls_atomic.h>
#include <bsls_keyword.h>
#include <bsl_memory.h>

namespace BloombergLP {
namespace ntcs {

/// @internal @brief
/// Enumerate the attachment state of a proactor socket to its proactor.
///
/// @par Thread Safety
/// This class is thread safe.
///
/// @ingroup module_ntcs
struct ProactorDetachState {
    /// Enumerate the attachment state of a proactor socket to its proactor.
    enum Value {
        /// The proactor socket is attached to its proactor. Zero or more
        /// threads may be processing the socket.
        e_ATTACHED,

        /// The user has initiated an asynchronous detachment of a proactor
        /// socket from its proactor, but the completion function for that
        /// operation has not yet been scheduled to be invoked because at least
        /// one thread is still processing the socket.
        e_DETACHING,

        /// The user has initiated an asynchronous detachment of a proactor
        /// socket and the completion function for that operation has been (or
        /// should be) scheduled to be invoked.
        e_DETACHED
    };
};

/// @internal @brief
/// Provide a mechanism to manage the states of a proactor socket with respect
/// to its detachment from its proactor.
///
/// @par Terminology
/// The contract and implementation of this class uses the following
/// terminology:
///
/// @li @b Attached:
/// The proactor socket is attached to its proactor. Zero or more threads may
/// be processing the socket.
///
/// @li @b Detaching:
/// The user has initiated an asynchronous detachment of a proactor socket from
/// its proactor, but the completion function for that operation has not yet
/// been scheduled to be invoked because at least one thread is still
/// processing the socket.
///
/// @li @b Detached:
/// The user has initiated an asynchronous detachment of a proactor socket and
/// the completion function for that operation has been (or should be)
/// scheduled to be invoked.
///
/// @par Thread Safety
/// This class is thread safe.
///
/// @ingroup module_ntcs
class ProactorDetachContext
{
    /// The socket is attached to its proactor and the user has not
    /// initiated a detachment.
    ///
    /// Binary representation: 00000000 00000000 00000000 00000000
    static const unsigned int k_ATTACHED = 0;

    /// The user has initiated a detachment of the socket from its
    /// proactor, but the callback has not yet been invoked.
    ///
    /// Binary representation: 01000000 00000000 00000000 00000000
    static const unsigned int k_DETACHING = 1 << 30;

    /// The user has initiated a detachment of the socket from its proactor
    /// and the callback as been invoked (or enqueued onto a strand to be
    /// invoked asynchronously.)
    ///
    /// Binary representation: 10000000 00000000 00000000 00000000
    static const unsigned int k_DETACHED = 1 << 31;

    /// The mask of the bits to store the number of threads actively
    /// working on the socket.
    ///
    /// Binary representation: 00111111 11111111 11111111 11111111
    static const unsigned int k_COUNT_MASK = 0x3FFFFFFF;

    /// The mask of the bits used to store the detched state.
    ///
    /// Binary representation: 11000000 00000000 00000000 00000000
    static const unsigned int k_STATE_MASK = 0xC0000000;

    /// The combined state and number of processors.
    bsls::AtomicUint d_value;

  private:
    ProactorDetachContext(const ProactorDetachContext&) BSLS_KEYWORD_DELETED;
    ProactorDetachContext& operator=(const ProactorDetachContext&)
        BSLS_KEYWORD_DELETED;

    /// Atomically update 'd_state' to the specified 'newValue' if it equals
    /// the specified 'oldValue'. Return true if 'd_value' was updated,
    /// otherwise return false.
    bool update(unsigned int oldValue, unsigned int newValue);

  public:
    /// Create a new proactor socket detachment context initially in the
    /// attached state with zero current threads actively working on the
    /// socket.
    ProactorDetachContext();

    /// Destroy this object.
    ~ProactorDetachContext();

    /// Increment the number of threads actively working on the socket. Return
    /// true if the socket is attached, and false if the socket is detaching
    /// or is detached. Note that when this function returns false the caller
    /// must avoid working on the socket.
    bool incrementReference();

    /// Decrement the number of threads actively working on the socket. Return
    /// true if the socket is now detached, and false if the socket is still
    /// attached or is detaching. Note that when this function returns true
    /// it is the caller's responsibility to invoke the asynchronous detachment
    /// completion function.
    bool decrementReference();

    /// Transistion to the detaching or detached state, depending on the number
    /// of threads actively working on the socket: if there are no threads
    /// actively working on the socket, the socket is now detached, otherwise
    /// the socket is detaching. Return success if the socket is now detached,
    /// ntsa::Error::e_WOULD_BLOCK if the socket was attached but is now
    /// detaching, and ntsa::Error::e_INVALID if the socket was already
    /// detaching or detached. Note that when this function returns success it
    /// is the caller's responsibility to invoke the asynchronous detachment
    /// completion function.
    ntsa::Error detach();

    /// Return the number of threads actively working on the socket.
    bsl::size_t numProcessors() const;

    /// Return the detachment state.
    ProactorDetachState::Value state() const;
};

/// @internal @brief
/// Provide a guard to automatically decrement the number of processors of a
/// proactor socket and, if appropriate, schedule the completion of the
/// asynchronous detachment operation.
///
/// @par Thread Safety
/// This class is not thread safe.
///
/// @ingroup module_ntcs
class ProactorDetachGuard
{
    bsl::shared_ptr<ntci::ProactorSocket>        d_socket_sp;
    bsl::shared_ptr<ntcs::ProactorDetachContext> d_context_sp;
    bool                                         d_authorization;

  private:
    ProactorDetachGuard(const ProactorDetachGuard&) BSLS_KEYWORD_DELETED;
    ProactorDetachGuard& operator=(const ProactorDetachGuard&)
        BSLS_KEYWORD_DELETED;

  public:
    /// Create a new guard, detect if operation on the specified 'socket' is
    /// authorized, and if so, automatically increment the number of processors
    /// of the 'socket'. Note that authorization is indicated by evaluating
    /// the resulting object as a boolean.
    explicit ProactorDetachGuard(
        const bsl::shared_ptr<ntci::ProactorSocket>& socket);

    /// Unless otherwise released, decrement the number of processors of the
    /// underlying socket if the guard authorized the caller to operate of the
    /// socket, schedule the completion of the asynchronous socket detach
    /// operation, if appropriate, and destroy this object.
    ~ProactorDetachGuard();

    /// Release the guard from managing the underlying socket.
    void release();

    /// Return true if the guard authorizes the calling thread to actively work
    /// on the socket, otherwise return false.
    operator bool() const;
};

NTCCFG_INLINE
bool ProactorDetachContext::update(unsigned int oldValue,
                                   unsigned int newValue)
{
    return d_value.testAndSwapAcqRel(oldValue, newValue) == oldValue;
}

NTCCFG_INLINE
ProactorDetachContext::ProactorDetachContext()
: d_value(0)
{
}

NTCCFG_INLINE
ProactorDetachContext::~ProactorDetachContext()
{
}

NTCCFG_INLINE
bool ProactorDetachContext::incrementReference()
{
    while (true) {
        unsigned int currentValue = d_value.loadAcquire();
        unsigned int currentState = currentValue & k_STATE_MASK;
        unsigned int currentCount = currentValue & k_COUNT_MASK;

        if (currentState == k_ATTACHED) {
            if (update(currentValue, k_ATTACHED | (currentCount + 1))) {
                return true;
            }
        }
        else {
            return false;
        }
    }
}

NTCCFG_INLINE
bool ProactorDetachContext::decrementReference()
{
    while (true) {
        const unsigned int currentValue = d_value.loadAcquire();
        const unsigned int currentState = currentValue & k_STATE_MASK;
        const unsigned int currentCount = currentValue & k_COUNT_MASK;

        if (currentState == k_ATTACHED) {
            BSLS_ASSERT(currentCount > 0);
            if (update(currentValue, k_ATTACHED | (currentCount - 1))) {
                return false;
            }
        }
        else if (currentState == k_DETACHING) {
            if (currentCount == 1) {
                if (update(currentValue, k_DETACHED)) {
                    return true;
                }
            }
            else {
                BSLS_ASSERT(currentCount > 1);
                if (update(currentValue, k_DETACHING | (currentCount - 1))) {
                    return false;
                }
            }
        }
        else {
            BSLS_ASSERT_OPT(currentState != k_DETACHED);
        }
    }
}

NTCCFG_INLINE
ntsa::Error ProactorDetachContext::detach()
{
    while (true) {
        const unsigned int currentValue = d_value.loadAcquire();
        const unsigned int currentState = currentValue & k_STATE_MASK;
        const unsigned int currentCount = currentValue & k_COUNT_MASK;

        if (currentState == k_ATTACHED) {
            if (currentCount == 0) {
                if (update(currentValue, k_DETACHED)) {
                    return ntsa::Error();
                }
            }
            else {
                BSLS_ASSERT(currentCount > 0);
                if (update(currentValue, k_DETACHING | currentCount)) {
                    return ntsa::Error(ntsa::Error::e_WOULD_BLOCK);
                }
            }
        }
        else {
            return ntsa::Error(ntsa::Error::e_INVALID);
        }
    }
}

NTCCFG_INLINE
bsl::size_t ProactorDetachContext::numProcessors() const
{
    const unsigned int currentValue = d_value.loadAcquire();
    const unsigned int currentCount = currentValue & k_COUNT_MASK;

    return static_cast<bsl::size_t>(currentCount);
}

NTCCFG_INLINE
ProactorDetachState::Value ProactorDetachContext::state() const
{
    const unsigned int currentValue = d_value.loadAcquire();
    const unsigned int currentState = currentValue & k_STATE_MASK;

    switch (currentState) {
    case k_ATTACHED:
        return ProactorDetachState::e_ATTACHED;
    case k_DETACHING:
        return ProactorDetachState::e_DETACHING;
    case k_DETACHED:
        return ProactorDetachState::e_DETACHED;
    }

    NTCCFG_UNREACHABLE();
    return ProactorDetachState::e_ATTACHED;
}

NTCCFG_INLINE
ProactorDetachGuard::ProactorDetachGuard(
    const bsl::shared_ptr<ntci::ProactorSocket>& socket)
: d_socket_sp(socket)
, d_context_sp()
, d_authorization(false)
{
    if (d_socket_sp) {
        d_context_sp =
            bslstl::SharedPtrUtil::staticCast<ntcs::ProactorDetachContext>(
                d_socket_sp->getProactorContext());

        if (d_context_sp) {
            d_authorization = d_context_sp->incrementReference();
        }
    }
}

NTCCFG_INLINE
ProactorDetachGuard::~ProactorDetachGuard()
{
    if (d_context_sp) {
        if (d_authorization) {
            const bool announce = d_context_sp->decrementReference();
            if (announce) {
                if (d_socket_sp) {
                    d_socket_sp->setProactorContext(bsl::shared_ptr<void>());
                    ntcs::Dispatch::announceDetached(d_socket_sp,
                                                     d_socket_sp->strand());
                }
            }
        }
    }
}

NTCCFG_INLINE
void ProactorDetachGuard::release()
{
    d_socket_sp.reset();
    d_context_sp.reset();
    d_authorization = false;
}

/// Return true if the guard authorizes the calling thread to actively work
/// on the socket, otherwise return false.
NTCCFG_INLINE
ProactorDetachGuard::operator bool() const
{
    return d_authorization;
}

}  // end namespace ntcs
}  // end namespace BloombergLP
#endif
