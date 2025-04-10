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

#ifndef INCLUDED_NTCA_GETDOMAINNAMECONTEXT
#define INCLUDED_NTCA_GETDOMAINNAMECONTEXT

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

#include <ntca_resolversource.h>
#include <ntccfg_platform.h>
#include <ntcscm_version.h>
#include <ntsa_endpoint.h>
#include <ntsa_error.h>
#include <ntsa_ipaddress.h>
#include <bdlb_nullablevalue.h>
#include <bslh_hash.h>
#include <bsls_timeinterval.h>
#include <bsl_iosfwd.h>
#include <bsl_string.h>

namespace BloombergLP {
namespace ntca {

/// Describe the context of an operation to get the domain name to which an
/// IP address is assigned.
///
/// @par Attributes
/// This class is composed of the following attributes.
///
/// @li @b ipAddress:
/// The IP address requested to be resolved.
///
/// @li @b latency:
/// The length of time to perform the resolution.
///
/// @li @b source:
/// The source of the resolution.
///
/// @li @b nameServer:
/// The endpoint of the name server that successfully responded to the request,
/// if any.
///
/// @li @b timeToLive:
/// The relative duration the results of the operation should be cached, in
/// seconds, if known.
///
/// @li @b error:
/// The error detected when performing the operation.
///
/// @par Thread Safety
/// This class is not thread safe.
///
/// @ingroup module_ntci_operation_resolve
class GetDomainNameContext
{
    ntsa::IpAddress                     d_ipAddress;
    bsls::TimeInterval                  d_latency;
    ntca::ResolverSource::Value         d_source;
    bdlb::NullableValue<ntsa::Endpoint> d_nameServer;
    bdlb::NullableValue<bsl::size_t>    d_timeToLive;
    ntsa::Error                         d_error;

  public:
    /// Create a new get domain name context having the default value.
    /// Optionally specify a 'basicAllocator' used to supply memory. If
    /// 'basicAllocator' is 0, the currently installed default allocator is
    /// used.
    explicit GetDomainNameContext(bslma::Allocator* basicAllocator = 0);

    /// Create a new get domain name context having the same value as the
    /// specified 'original' object. Optionally specify a 'basicAllocator'
    /// used to supply memory. If 'basicAllocator' is 0, the currently
    /// installed default allocator is used.
    GetDomainNameContext(const GetDomainNameContext& original,
                         bslma::Allocator*           basicAllocator = 0);

    /// Destroy this object.
    ~GetDomainNameContext();

    /// Assign the value of the specified 'other' object to this object.
    /// Return a reference to this modifiable object.
    GetDomainNameContext& operator=(const GetDomainNameContext& other);

    /// Reset the value of this object to its value upon default
    /// construction.
    void reset();

    /// Set the IP address requested to be resolved to the specified
    /// 'value'.
    void setIpAddress(const ntsa::IpAddress& value);

    /// Set the length of time to perform the resolution to the specified
    /// 'value'.
    void setLatency(const bsls::TimeInterval& value);

    /// Set the source of the resolution to the specified 'value'.
    void setSource(ntca::ResolverSource::Value value);

    /// Set the endpoint of the name server that successfully responded to
    /// the request to the specified 'value'.
    void setNameServer(const ntsa::Endpoint& value);

    /// Set the time-to-live for the results on the operation to the
    /// specified 'value'.
    void setTimeToLive(bsl::size_t value);

    /// Set the error detected when performing the operation to the
    /// specified 'value'.
    void setError(const ntsa::Error& value);

    /// Return the IP address requested to be resolved.
    const ntsa::IpAddress& ipAddress() const;

    /// Return the length of time to perform the resolution.
    const bsls::TimeInterval& latency() const;

    /// Return the source of the resolution.
    ntca::ResolverSource::Value source() const;

    /// Return the endpoint of the name server that successfully responded
    /// to the request.
    const bdlb::NullableValue<ntsa::Endpoint>& nameServer() const;

    /// Return the time-to-live for the results on the operation.
    const bdlb::NullableValue<bsl::size_t>& timeToLive() const;

    /// Return the error detected when performing the operation.
    const ntsa::Error& error() const;

    /// Return true if this object has the same value as the specified
    /// 'other' object, otherwise return false.
    bool equals(const GetDomainNameContext& other) const;

    /// Return true if the value of this object is less than the value of
    /// the specified 'other' object, otherwise return false.
    bool less(const GetDomainNameContext& other) const;

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

    /// This type accepts an allocator argument to its constructors and may
    /// dynamically allocate memory during its operation.
    NTSCFG_TYPE_TRAIT_ALLOCATOR_AWARE(GetDomainNameContext);
};

/// Write the specified 'object' to the specified 'stream'. Return
/// a modifiable reference to the 'stream'.
///
/// @related ntca::GetDomainNameContext
bsl::ostream& operator<<(bsl::ostream&               stream,
                         const GetDomainNameContext& object);

/// Return true if the specified 'lhs' has the same value as the specified
/// 'rhs', otherwise return false.
///
/// @related ntca::GetDomainNameContext
bool operator==(const GetDomainNameContext& lhs,
                const GetDomainNameContext& rhs);

/// Return true if the specified 'lhs' does not have the same value as the
/// specified 'rhs', otherwise return false.
///
/// @related ntca::GetDomainNameContext
bool operator!=(const GetDomainNameContext& lhs,
                const GetDomainNameContext& rhs);

/// Return true if the value of the specified 'lhs' is less than the value
/// of the specified 'rhs', otherwise return false.
///
/// @related ntca::GetDomainNameContext
bool operator<(const GetDomainNameContext& lhs,
               const GetDomainNameContext& rhs);

/// Contribute the values of the salient attributes of the specified 'value'
/// to the specified hash 'algorithm'.
///
/// @related ntca::GetDomainNameContext
template <typename HASH_ALGORITHM>
void hashAppend(HASH_ALGORITHM& algorithm, const GetDomainNameContext& value);

NTCCFG_INLINE
GetDomainNameContext::GetDomainNameContext(bslma::Allocator* basicAllocator)
: d_ipAddress()
, d_latency()
, d_source(ntca::ResolverSource::e_UNKNOWN)
, d_nameServer()
, d_timeToLive()
, d_error()
{
    NTCCFG_WARNING_UNUSED(basicAllocator);
}

NTCCFG_INLINE
GetDomainNameContext::GetDomainNameContext(
    const GetDomainNameContext& original,
    bslma::Allocator*           basicAllocator)
: d_ipAddress(original.d_ipAddress)
, d_latency(original.d_latency)
, d_source(original.d_source)
, d_nameServer(original.d_nameServer)
, d_timeToLive(original.d_timeToLive)
, d_error(original.d_error)
{
    NTCCFG_WARNING_UNUSED(basicAllocator);
}

NTCCFG_INLINE
GetDomainNameContext::~GetDomainNameContext()
{
}

NTCCFG_INLINE
GetDomainNameContext& GetDomainNameContext::operator=(
    const GetDomainNameContext& other)
{
    if (this != &other) {
        d_ipAddress  = other.d_ipAddress;
        d_latency    = other.d_latency;
        d_source     = other.d_source;
        d_nameServer = other.d_nameServer;
        d_timeToLive = other.d_timeToLive;
        d_error      = other.d_error;
    }
    return *this;
}

NTCCFG_INLINE
void GetDomainNameContext::reset()
{
    d_ipAddress.reset();
    d_latency = bsls::TimeInterval();
    d_source  = ntca::ResolverSource::e_UNKNOWN;
    d_nameServer.reset();
    d_timeToLive.reset();
    d_error = ntsa::Error();
}

NTCCFG_INLINE
void GetDomainNameContext::setIpAddress(const ntsa::IpAddress& value)
{
    d_ipAddress = value;
}

NTCCFG_INLINE
void GetDomainNameContext::setLatency(const bsls::TimeInterval& value)
{
    d_latency = value;
}

NTCCFG_INLINE
void GetDomainNameContext::setSource(ntca::ResolverSource::Value value)
{
    d_source = value;
}

NTCCFG_INLINE
void GetDomainNameContext::setNameServer(const ntsa::Endpoint& value)
{
    d_nameServer = value;
}

NTCCFG_INLINE
void GetDomainNameContext::setTimeToLive(bsl::size_t value)
{
    d_timeToLive = value;
}

NTCCFG_INLINE
void GetDomainNameContext::setError(const ntsa::Error& value)
{
    d_error = value;
}

NTCCFG_INLINE
const ntsa::IpAddress& GetDomainNameContext::ipAddress() const
{
    return d_ipAddress;
}

NTCCFG_INLINE
const bsls::TimeInterval& GetDomainNameContext::latency() const
{
    return d_latency;
}

NTCCFG_INLINE
ntca::ResolverSource::Value GetDomainNameContext::source() const
{
    return d_source;
}

NTCCFG_INLINE
const bdlb::NullableValue<ntsa::Endpoint>& GetDomainNameContext::nameServer()
    const
{
    return d_nameServer;
}

NTCCFG_INLINE
const bdlb::NullableValue<bsl::size_t>& GetDomainNameContext::timeToLive()
    const
{
    return d_timeToLive;
}

NTCCFG_INLINE
const ntsa::Error& GetDomainNameContext::error() const
{
    return d_error;
}

NTCCFG_INLINE
bsl::ostream& operator<<(bsl::ostream&               stream,
                         const GetDomainNameContext& object)
{
    return object.print(stream, 0, -1);
}

NTCCFG_INLINE
bool operator==(const GetDomainNameContext& lhs,
                const GetDomainNameContext& rhs)
{
    return lhs.equals(rhs);
}

NTCCFG_INLINE
bool operator!=(const GetDomainNameContext& lhs,
                const GetDomainNameContext& rhs)
{
    return !operator==(lhs, rhs);
}

NTCCFG_INLINE
bool operator<(const GetDomainNameContext& lhs,
               const GetDomainNameContext& rhs)
{
    return lhs.less(rhs);
}

template <typename HASH_ALGORITHM>
void hashAppend(HASH_ALGORITHM& algorithm, const GetDomainNameContext& value)
{
    using bslh::hashAppend;

    hashAppend(algorithm, value.ipAddress());
    hashAppend(algorithm, value.latency());
    hashAppend(algorithm, value.source());
    hashAppend(algorithm, value.nameServer());
    hashAppend(algorithm, value.timeToLive());
    hashAppend(algorithm, value.error());
}

}  // close package namespace
}  // close enterprise namespace
#endif
