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

#ifndef INCLUDED_NTCA_ACCEPTEVENT
#define INCLUDED_NTCA_ACCEPTEVENT

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

#include <ntca_acceptcontext.h>
#include <ntca_accepteventtype.h>
#include <ntccfg_platform.h>
#include <ntcscm_version.h>
#include <bslh_hash.h>
#include <bsl_iosfwd.h>

namespace BloombergLP {
namespace ntca {

/// Describe an event detected for an asynchronous accept operation.
///
/// @par Attributes
/// This class is composed of the following attributes.
///
/// @li @b type:
/// The type of accept event.
///
/// @li @b context:
/// The context of the accept operation at the time of the event.
///
/// @par Thread Safety
/// This class is not thread safe.
///
/// @ingroup module_ntci_operation_accept
class AcceptEvent
{
    ntca::AcceptEventType::Value d_type;
    ntca::AcceptContext          d_context;

  public:
    /// Create a new accept event having the default value.
    AcceptEvent();

    /// Create a new accept event having the same value as the specified
    /// 'original' object.
    AcceptEvent(const AcceptEvent& original);

    /// Destroy this object.
    ~AcceptEvent();

    /// Assign the value of the specified 'other' object to this object.
    /// Return a reference to this modifiable object.
    AcceptEvent& operator=(const AcceptEvent& other);

    /// Reset the value of this object to its value upon default
    /// construction.
    void reset();

    /// Set the type of accept event to the specified 'value'.
    void setType(ntca::AcceptEventType::Value value);

    /// Set the context of the accept operation at the time of the event to
    /// the specified 'value'.
    void setContext(const ntca::AcceptContext& value);

    /// Return the type of accept event.
    ntca::AcceptEventType::Value type() const;

    /// Return the context of the accept operation at the time of the event.
    const ntca::AcceptContext& context() const;

    /// Return true if 'type() == ntca::AcceptEventType::e_COMPLETE', i.e.,
    /// the accept operation successfully completed without an error.
    /// Otherwise, return false.
    bool isComplete() const;

    /// Return true if 'type() == ntca::AcceptEventType::e_ERROR', i.e.,
    /// the accept operation failed because of an error. Otherwise, return
    /// false. Note that the exact error is stored at 'context().error()'.
    bool isError() const;

    /// Return true if this object has the same value as the specified
    /// 'other' object, otherwise return false.
    bool equals(const AcceptEvent& other) const;

    /// Return true if the value of this object is less than the value of
    /// the specified 'other' object, otherwise return false.
    bool less(const AcceptEvent& other) const;

    /// Format this object to the specified output 'stream' at the
    /// optionally specified indentation 'level' and return a reference to
    /// the modifiable 'stream'.  If 'level' is specified, optionally
    /// specify 'spacesPerLevel', the number of spaces per indentation level
    /// for this and all of its nested objects.  Each line is indented by
    /// the absolute value of 'level * spacesPerLevel'.  If 'level' is
    /// negative, suppress indentation of the first line.  If
    /// 'spacesPerLevel' is negative, suppress line breaks and format the
    /// entire output on one line.  If 'stream' is initially invalid, this
    /// operation has no effect.  Note that a trailing newline is provided
    /// in multiline mode only.
    bsl::ostream& print(bsl::ostream& stream,
                        int           level          = 0,
                        int           spacesPerLevel = 4) const;

    /// This type's copy-constructor and copy-assignment operator is equivalent
    /// to copying each byte of the source object's footprint to each
    /// corresponding byte of the destination object's footprint.
    NTSCFG_TYPE_TRAIT_BITWISE_COPYABLE(AcceptEvent);

    /// This type's move-constructor and move-assignment operator is equivalent
    /// to copying each byte of the source object's footprint to each
    /// corresponding byte of the destination object's footprint.
    NTSCFG_TYPE_TRAIT_BITWISE_MOVABLE(AcceptEvent);
};

/// Write the specified 'object' to the specified 'stream'. Return
/// a modifiable reference to the 'stream'.
///
/// @related ntca::AcceptEvent
bsl::ostream& operator<<(bsl::ostream& stream, const AcceptEvent& object);

/// Return true if the specified 'lhs' has the same value as the specified
/// 'rhs', otherwise return false.
///
/// @related ntca::AcceptEvent
bool operator==(const AcceptEvent& lhs, const AcceptEvent& rhs);

/// Return true if the specified 'lhs' does not have the same value as the
/// specified 'rhs', otherwise return false.
///
/// @related ntca::AcceptEvent
bool operator!=(const AcceptEvent& lhs, const AcceptEvent& rhs);

/// Return true if the value of the specified 'lhs' is less than the value
/// of the specified 'rhs', otherwise return false.
///
/// @related ntca::AcceptEvent
bool operator<(const AcceptEvent& lhs, const AcceptEvent& rhs);

/// Contribute the values of the salient attributes of the specified 'value'
/// to the specified hash 'algorithm'.
///
/// @related ntca::AcceptEvent
template <typename HASH_ALGORITHM>
void hashAppend(HASH_ALGORITHM& algorithm, const AcceptEvent& value);

NTCCFG_INLINE
AcceptEvent::AcceptEvent()
: d_type(ntca::AcceptEventType::e_COMPLETE)
, d_context()
{
}

NTCCFG_INLINE
AcceptEvent::AcceptEvent(const AcceptEvent& original)
: d_type(original.d_type)
, d_context(original.d_context)
{
}

NTCCFG_INLINE
AcceptEvent::~AcceptEvent()
{
}

NTCCFG_INLINE
AcceptEvent& AcceptEvent::operator=(const AcceptEvent& other)
{
    d_type    = other.d_type;
    d_context = other.d_context;
    return *this;
}

NTCCFG_INLINE
void AcceptEvent::reset()
{
    d_type = ntca::AcceptEventType::e_COMPLETE;
    d_context.reset();
}

NTCCFG_INLINE
void AcceptEvent::setType(ntca::AcceptEventType::Value value)
{
    d_type = value;
}

NTCCFG_INLINE
void AcceptEvent::setContext(const ntca::AcceptContext& context)
{
    d_context = context;
}

NTCCFG_INLINE
ntca::AcceptEventType::Value AcceptEvent::type() const
{
    return d_type;
}

NTCCFG_INLINE
const ntca::AcceptContext& AcceptEvent::context() const
{
    return d_context;
}

NTCCFG_INLINE
bool AcceptEvent::isComplete() const
{
    return d_type == ntca::AcceptEventType::e_COMPLETE;
}

NTCCFG_INLINE
bool AcceptEvent::isError() const
{
    return d_type == ntca::AcceptEventType::e_ERROR;
}

NTCCFG_INLINE
bsl::ostream& operator<<(bsl::ostream& stream, const AcceptEvent& object)
{
    return object.print(stream, 0, -1);
}

NTCCFG_INLINE
bool operator==(const AcceptEvent& lhs, const AcceptEvent& rhs)
{
    return lhs.equals(rhs);
}

NTCCFG_INLINE
bool operator!=(const AcceptEvent& lhs, const AcceptEvent& rhs)
{
    return !operator==(lhs, rhs);
}

NTCCFG_INLINE
bool operator<(const AcceptEvent& lhs, const AcceptEvent& rhs)
{
    return lhs.less(rhs);
}

template <typename HASH_ALGORITHM>
void hashAppend(HASH_ALGORITHM& algorithm, const AcceptEvent& value)
{
    using bslh::hashAppend;

    hashAppend(algorithm, value.type());
    hashAppend(algorithm, value.context());
}

}  // close package namespace
}  // close enterprise namespace
#endif
