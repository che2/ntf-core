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

#ifndef INCLUDED_NTCA_DATAGRAMSOCKETOPTIONS
#define INCLUDED_NTCA_DATAGRAMSOCKETOPTIONS

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

#include <ntca_compressionconfig.h>
#include <ntca_serializationconfig.h>
#include <ntca_loadbalancingoptions.h>
#include <ntccfg_platform.h>
#include <ntcscm_version.h>
#include <ntsa_endpoint.h>
#include <ntsa_transport.h>
#include <bdlb_nullablevalue.h>
#include <bsl_iosfwd.h>

namespace BloombergLP {
namespace ntca {

/// Describe the configuration of a datagram socket.
///
/// @par Attributes
/// This class is composed of the following attributes.
///
/// @li @b transport:
/// The socket address family, protocol, and mode.
///
/// @li @b sourceEndpoint:
/// The source endpoint to which the socket is automatically bound, if any. If
/// this value is undefined the socket is not automatically bound but may be
/// explicitly bound after being opened, before connecting or sending, or may
/// be implicitly bound as a result of connecting or sending. Setting this
/// value automatically sets the transport.
///
/// @li @b reuseAddress:
/// The flag that indicates the operating system should allow the user to
/// rebind a socket to reuse local addresses.
///
/// @li @b readQueueLowWatermark:
/// The starting limit on the minimum size of the read queue required to call a
/// user read callback.
///
/// @li @b readQueueHighWatermark:
/// The maximum size of the read queue before the connection is automatically
/// closed.
///
/// @li @b writeQueueLowWatermark:
/// The size the write queue must be drained down to before the implementation
/// announces a low watermark event.
///
/// @li @b writeQueueHighWatermark:
/// The maximum size of the write queue that, once eclipsed, rejects subsequent
/// writes until the write queue has been drained back down to this limit.
///
/// @li @b sendGreedily:
/// The flag indicating that data should be repeatedly copied from the write
/// queue to the socket send buffer until the operating system indicates the
/// send buffer is full. If false, only one copy attempt is made each time the
/// operating system indicates that the send buffer has capacity available.
/// When set to true, this option indicates the user favors a lower minimum
/// latency and higher maximum throughput for an individual connection, at the
/// expense of more varying latency and throughput over all connections. When
/// set to false, this option indicates the user favors fairness and less
/// variance in throughput and latency over all connections, and the expense of
/// higher average latency and lower average throughput.
///
/// @li @b receiveGreedily:
/// The flag indicating that data should be repeatedly copied from the socket
/// receive buffer to the read queue until the operating system indicates the
/// receive buffer is empty. If false, only one copy attempt is made each time
/// the operating system indicates that the receive buffer is non-empty. When
/// set to true, this option indicates the user favors a lower minimum latency
/// and higher maximum throughput for an individual connection, at the expense
/// of more varying latency and throughput over all connections. When set to
/// false, this option indicates the user favors fairness and less variance in
/// throughput and latency over all connections, and the expense of higher
/// average latency and lower average throughput.
///
/// @li @b sendBufferSize:
/// The maximum size of each socket send buffer. On some platforms, this
/// options may serve simply as a hint.
///
/// @li @b receiveBufferSize:
/// The maximum size of each socket receive buffer. On some platforms, this
/// options may serve simply as a hint.
///
/// @li @b sendBufferLowWatermark:
/// The amount of available capacity that must exist in the socket send buffer
/// for the operating system to indicate the socket is writable.
///
/// @li @b receiveBufferLowWatermark:
/// The amount of available data that must exist in the socket receive buffer
/// for the operating system to indicate the socket is readable.
///
/// @li @b sendTimeout:
/// The amount of time a blocking send operation must complete before it is
/// deemed to have failed. This option is not widely supported and should be
/// avoided.
///
/// @li @b receiveTimeout:
/// The amount of time a blocking receive operation must complete before it is
/// deemed to have failed. This option is not widely supported and should be
/// avoided.
///
/// @li @b keepAlive:
/// That flag that indicates the operating system implementation should
/// periodically emit transport-level "keep-alive" packets.
///
/// @li @b noDelay:
/// The flag that indicates that subsequent writes should not be coalesced into
/// the larger packets that would otherwise form. When set to true, this option
/// indicates the user favors smaller latency at the expense of less network
/// efficiency. When set to false, this option indicates the user favors
/// greater network efficiency at the expense of greater latency.
///
/// @li @b debugFlag:
/// This flag indicates that each socket should be put into debug mode in the
/// operating system. The support and meaning of this option is
/// platform-specific.
///
/// @li @b allowBroadcasting:
/// The flag that indicates the socket supports sending to a broadcast address.
///
/// @li @b bypassNormalRouting:
/// The flag that indicates that normal routing rules are not used, the route
/// is based upon the destination address only.
///
/// @li @b leaveOutOfBandDataInline:
/// The flag that indicates out-of-band data should be placed into the normal
/// data input queue.
///
/// @li @b lingerFlag:
/// The flag that indicates the connection should be maintained after the user
/// closes it while data is still queued but be not transmitted.
///
/// @li @b lingerTimeout:
/// The amount of time a connection should linger after being closed to send
/// queued but untransmitted data.
///
/// @li @b maxDatagramSize:
/// The maximum size of each datagram.
///
/// @li @b multicastLoopback:
/// The flag that indicates a datagram sent to a multicast address should be
/// "looped back" to the sender when appropriate.
///
/// @li @b multicastTimeToLive:
/// The maximum number of router hops allowed for a multicast datagram.
///
/// @li @b multicastInterface:
/// The address if the network interface to transmit multicast datagrams.
///
/// @li @b keepHalfOpen:
/// When this option is true, when the socket has detected that the peer has
/// shutdown sending from the remote side of the connection, do not
/// automatically shut down sending from the local side of the connection and
/// close the socket; when the socket is shut down for sending from the local
/// side of the connection, do not automatically shut down receiving and close
/// the socket. When this option is false, when the socket either detects the
/// peer has shutdown sending from the remote side of the connection or shuts
/// down sending from the local side of the connection, the socket is also
/// automatically shutdown for receiving and closed.
///
/// @li @b metrics:
/// Collect metrics on socket behavior.
///
/// @li @b timestampOutgoingData:
/// The flag that indicates outgoing data should be timestamped.
///
/// @li @b timestampIncomingData:
/// The flag that indicates incoming data should be timestamped.
///
/// @li @b zeroCopyThreshold:
/// The minimum number of bytes that must be available to send in order to
/// attempt a zero-copy send.
///
/// @li @b loadBalancingOptions:
/// The configurable parameters used select a reactor or proactor that drives
/// the I/O for the socket.
///
/// @li @b compressionConfig:
/// The configurable parameters used to automatically apply compression to 
/// all outgoing and incoming traffic. If not specified, no compression is 
/// used.
///
/// @li @b serializationConfig:
/// The configurable parameters of the serialization mechanism used by this
/// socket.
///
/// @par Thread Safety
/// This class is not thread safe.
///
/// @ingroup module_ntci_socket
class DatagramSocketOptions
{
    ntsa::Transport::Value               d_transport;
    bdlb::NullableValue<ntsa::Endpoint>  d_sourceEndpoint;
    bool                                 d_reuseAddress;
    bdlb::NullableValue<bsl::size_t>     d_maxDatagramSize;
    bdlb::NullableValue<bsl::size_t>     d_readQueueLowWatermark;
    bdlb::NullableValue<bsl::size_t>     d_readQueueHighWatermark;
    bdlb::NullableValue<bsl::size_t>     d_writeQueueLowWatermark;
    bdlb::NullableValue<bsl::size_t>     d_writeQueueHighWatermark;
    bdlb::NullableValue<bool>            d_sendGreedily;
    bdlb::NullableValue<bool>            d_receiveGreedily;
    bdlb::NullableValue<bsl::size_t>     d_sendBufferSize;
    bdlb::NullableValue<bsl::size_t>     d_receiveBufferSize;
    bdlb::NullableValue<bsl::size_t>     d_sendBufferLowWatermark;
    bdlb::NullableValue<bsl::size_t>     d_receiveBufferLowWatermark;
    bdlb::NullableValue<bsl::size_t>     d_sendTimeout;
    bdlb::NullableValue<bsl::size_t>     d_receiveTimeout;
    bdlb::NullableValue<bool>            d_keepAlive;
    bdlb::NullableValue<bool>            d_noDelay;
    bdlb::NullableValue<bool>            d_debugFlag;
    bdlb::NullableValue<bool>            d_allowBroadcasting;
    bdlb::NullableValue<bool>            d_bypassNormalRouting;
    bdlb::NullableValue<bool>            d_leaveOutOfBandDataInline;
    bdlb::NullableValue<bool>            d_lingerFlag;
    bdlb::NullableValue<bsl::size_t>     d_lingerTimeout;
    bdlb::NullableValue<bool>            d_multicastLoopback;
    bdlb::NullableValue<bsl::size_t>     d_multicastTimeToLive;
    bdlb::NullableValue<ntsa::IpAddress> d_multicastInterface;
    bdlb::NullableValue<bool>            d_keepHalfOpen;
    bdlb::NullableValue<bool>            d_metrics;
    bdlb::NullableValue<bool>            d_timestampOutgoingData;
    bdlb::NullableValue<bool>            d_timestampIncomingData;
    bdlb::NullableValue<bsl::size_t>     d_zeroCopyThreshold;
    ntca::LoadBalancingOptions           d_loadBalancingOptions;
    bdlb::NullableValue<ntca::CompressionConfig> d_compressionConfig;
    bdlb::NullableValue<ntca::SerializationConfig> d_serializationConfig;

  public:
    /// Create new datagram socket options. Optionally specify a
    /// 'basicAllocator' used to supply memory. If 'basicAllocator' is 0, the
    /// currently installed default allocator is used.
    explicit DatagramSocketOptions(bslma::Allocator* basicAllocator = 0);

    /// Create new datagram socket options having the same value as the
    /// specified 'other' object. Optionally specify a 'basicAllocator' used to
    /// supply memory. If 'basicAllocator' is 0, the currently installed
    /// default allocator is used.
    DatagramSocketOptions(const DatagramSocketOptions& other, 
                          bslma::Allocator*            basicAllocator = 0);

    /// Destroy this object.
    ~DatagramSocketOptions();

    /// Assign the value of the specified 'other' object to this object.
    /// Return a reference to this modifiable object.
    DatagramSocketOptions& operator=(const DatagramSocketOptions& other);

    /// Set the transport to the specified 'value'.
    void setTransport(ntsa::Transport::Value value);

    /// Set the source endpoint of the datagram socket to the specified
    /// 'value'.
    void setSourceEndpoint(const ntsa::Endpoint& value);

    /// Set the option to enable binding to an address is use according to
    /// the specified 'value' flag.
    void setReuseAddress(bool value);

    /// Set the maximum datagram size to the specified 'value'.
    void setMaxDatagramSize(bsl::size_t value);

    /// Set the low watermark of the read queue to the specified 'value'.
    void setReadQueueLowWatermark(bsl::size_t value);

    /// Set the high watermark of the read queue to the specified 'value'.
    void setReadQueueHighWatermark(bsl::size_t value);

    /// Set the low watermark of the write queue to the specified 'value'.
    void setWriteQueueLowWatermark(bsl::size_t value);

    /// Set the high watermark of the write queue to the specified 'value'.
    void setWriteQueueHighWatermark(bsl::size_t value);

    /// Set the flag that controls greedy sends to the specified 'value'.
    void setSendGreedily(bool value);

    /// Set the flag that controls greedy receives to the specified 'value'.
    void setReceiveGreedily(bool value);

    /// Set the maximum size of the send buffer to the specified 'value'.
    void setSendBufferSize(bsl::size_t value);

    /// Set the maximum size of the receive buffer to the specified 'value'.
    void setReceiveBufferSize(bsl::size_t value);

    /// Set the minimum amount of capacity available in the send buffer
    /// before it is considered writable to the specified 'value'.
    void setSendBufferLowWatermark(bsl::size_t value);

    /// Set the minimum amount of data available in the receive buffer
    /// before it is considered readable to the specified 'value'.
    void setReceiveBufferLowWatermark(bsl::size_t value);

    /// Set the send timeout to the specified 'value'.
    void setSendTimeout(bsl::size_t value);

    /// Set the receive timeout to the specified 'value'.
    void setReceiveTimeout(bsl::size_t value);

    /// Set the flag enable protocol-level keep-alive messages to the
    /// specified 'value'.
    void setKeepAlive(bool value);

    /// Set the flag disabling protocol-level packet coalescing to the
    /// specified 'value'.
    void setNoDelay(bool value);

    /// Set the flag indicating debug information should be recorded.
    void setDebugFlag(bool value);

    /// Set the flag enabling broadcasting to the specified 'value'.
    void setAllowBroadcasting(bool value);

    /// Set the flag bypassing normal routing to the specified 'value'.
    void setBypassNormalRouting(bool value);

    /// Set the flag indicating that out-of-band data should be left
    /// inline to the specified 'value'.
    void setLeaveOutofBandDataInline(bool value);

    /// Set the linger flag to the specified 'value'.
    void setLingerFlag(bool value);

    /// Set the linger timeout, in seconds.
    void setLingerTimeout(bsl::size_t value);

    /// Set the flag that indicates multicast datagrams should be looped
    /// back to the local host to the specified 'value'.
    void setMulticastLoopback(bool value);

    /// Set the maximum number of hops over which multicast datagrams
    /// should be forwarded to the specified 'value'.
    void setMulticastTimeToLive(bsl::size_t value);

    /// Set the address of the network interface on which multicast
    /// datagrams should be sent to the specified 'value'.
    void setMulticastInterface(const ntsa::IpAddress& value);

    /// Set the flag indicating the socket should be kept half-open (i.e.,
    /// able to receive) even though transmission has been shutdown by
    /// either side of the connection to the specified 'value'.
    void setKeepHalfOpen(bool value);

    /// Set the flag indicating per-socket metrics should be collected to
    /// the specified 'value'.
    void setMetrics(bool value);

    /// Set the flag that indicates outgoing data should be timestamped to the
    /// specified 'value'.
    void setTimestampOutgoingData(bool value);

    /// Set the flag that indicates incoming data should be timestamped to the
    /// specified 'value'.
    void setTimestampIncomingData(bool value);

    /// Set the minimum number of bytes that must be available to send in order
    /// to attempt a zero-copy send to the specified 'value'.
    void setZeroCopyThreshold(bsl::size_t value);

    /// Set the load balancing options to the specified 'value'.
    void setLoadBalancingOptions(const ntca::LoadBalancingOptions& value);

    /// Set the compression configuration to the specified 'value'.
    void setCompressionConfig(const ntca::CompressionConfig& value);

    /// Set the serialization configuration to the specified 'value'.
    void setSerializationConfig(const ntca::SerializationConfig& value);

    /// Return the transport.
    ntsa::Transport::Value transport() const;

    /// Return the source endpoint of the datagram socket.
    const bdlb::NullableValue<ntsa::Endpoint>& sourceEndpoint() const;

    /// Return the option to enable binding to an address that is in use.
    bool reuseAddress() const;

    /// Return the maximum datagram size.
    const bdlb::NullableValue<bsl::size_t>& maxDatagramSize() const;

    /// Return the low watermark of the read queue.
    const bdlb::NullableValue<bsl::size_t>& readQueueLowWatermark() const;

    /// Return the high watermark of the read queue.
    const bdlb::NullableValue<bsl::size_t>& readQueueHighWatermark() const;

    /// Return the low watermark of the write queue.
    const bdlb::NullableValue<bsl::size_t>& writeQueueLowWatermark() const;

    /// Return the high watermark of the write queue.
    const bdlb::NullableValue<bsl::size_t>& writeQueueHighWatermark() const;

    /// Return the flag that controls greedy sends.
    const bdlb::NullableValue<bool>& sendGreedily() const;

    /// Return the flag that controls greedy receives.
    const bdlb::NullableValue<bool>& receiveGreedily() const;

    /// Return the maximum size of the send buffer.
    const bdlb::NullableValue<bsl::size_t>& sendBufferSize() const;

    /// Return the maximum size of the receive buffer.
    const bdlb::NullableValue<bsl::size_t>& receiveBufferSize() const;

    /// Return the minimum amount of capacity available in the send buffer
    /// before it is considered writable.
    const bdlb::NullableValue<bsl::size_t>& sendBufferLowWatermark() const;

    /// Return the minimum amount of data available in the receive buffer
    /// before it is considered readable.
    const bdlb::NullableValue<bsl::size_t>& receiveBufferLowWatermark() const;

    /// Return the send timeout.
    const bdlb::NullableValue<bsl::size_t>& sendTimeout() const;

    /// Return the receive timeout.
    const bdlb::NullableValue<bsl::size_t>& receiveTimeout() const;

    /// Return the flag enable protocol-level keep-alive messages.
    const bdlb::NullableValue<bool>& keepAlive() const;

    /// Return the flag disabling protocol-level packet coalescing.
    const bdlb::NullableValue<bool>& noDelay() const;

    /// Return the flag indicating debug information should be recorded.
    const bdlb::NullableValue<bool>& debugFlag() const;

    /// Return the flag enabling broadcasting .
    const bdlb::NullableValue<bool>& allowBroadcasting() const;

    /// Return the flag bypassing normal routing.
    const bdlb::NullableValue<bool>& bypassNormalRouting() const;

    /// Return the flag indicating that out-of-band data should be left
    /// inline.
    const bdlb::NullableValue<bool>& leaveOutofBandDataInline() const;

    /// Return the linger flag.
    const bdlb::NullableValue<bool>& lingerFlag() const;

    /// Return the linger timeout, in seconds.
    const bdlb::NullableValue<bsl::size_t>& lingerTimeout() const;

    /// Return flag that indicates multicast datagrams should be looped
    /// back to the local host.
    const bdlb::NullableValue<bool>& multicastLoopback() const;

    /// Return the maximum number of hops over which multicast datagrams
    /// should be forwarded.
    const bdlb::NullableValue<bsl::size_t>& multicastTimeToLive() const;

    /// Return the address of the network interface on which multicast
    /// datagrams should be sent.
    const bdlb::NullableValue<ntsa::IpAddress>& multicastInterface() const;

    /// Return the flag indicating the socket should be kept half-open
    /// (i.e., able to receive) even though transmission has been shutdown
    /// by either side of the connection.
    const bdlb::NullableValue<bool>& keepHalfOpen() const;

    /// Return the flag indicating per-socket metrics should be collected.
    const bdlb::NullableValue<bool>& metrics() const;

    /// Return the flag that indicates outgoing data should be timestamped.
    const bdlb::NullableValue<bool>& timestampOutgoingData() const;

    /// Return the flag that indicates incoming data should be timestamped.
    const bdlb::NullableValue<bool>& timestampIncomingData() const;

    /// Return the minimum number of bytes that must be available to send in
    /// order to attempt a zero-copy send.
    const bdlb::NullableValue<bsl::size_t>& zeroCopyThreshold() const;

    /// Return the load balancing options.
    const ntca::LoadBalancingOptions& loadBalancingOptions() const;

    /// Return the compression configuration.
    const bdlb::NullableValue<ntca::CompressionConfig>& 
    compressionConfig() const;

    /// Return the serialization configuration.
    const bdlb::NullableValue<ntca::SerializationConfig>& 
    serializationConfig() const;

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
};

/// Return 'true' if the specified 'lhs' and 'rhs' attribute objects have
/// the same value, and 'false' otherwise.  Two attribute objects have the
/// same value if each respective attribute has the same value.
///
/// @related ntca::DatagramSocketOptions
bool operator==(const DatagramSocketOptions& lhs,
                const DatagramSocketOptions& rhs);

/// Return 'true' if the specified 'lhs' and 'rhs' attribute objects do not
/// have the same value, and 'false' otherwise.  Two attribute objects do
/// not have the same value if one or more respective attributes differ in
/// values.
///
/// @related ntca::DatagramSocketOptions
bool operator!=(const DatagramSocketOptions& lhs,
                const DatagramSocketOptions& rhs);

/// Format the specified 'object' to the specified output 'stream' and
/// return a reference to the modifiable 'stream'.
///
/// @related ntca::DatagramSocketOptions
bsl::ostream& operator<<(bsl::ostream&                stream,
                         const DatagramSocketOptions& object);

}  // close package namespace
}  // close enterprise namespace
#endif
