#ifndef __NETKIT_IO_SOCKETADDRESS_HPP
#define __NETKIT_IO_SOCKETADDRESS_HPP
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <stdexcept>

namespace NetKit
{

namespace IO
{

typedef union address
{
	struct sockaddr sa;
	struct sockaddr_in sa_in;
	struct sockaddr_in6 sa_in6;
	struct sockaddr_storage sa_stor;
}
address_t;

/**
 * \brief SocketAddress is used for resolving and storing remote addresses.
 */
class SocketAddress
{
public:
	enum AddressFamily
	{
		IPv4Address,
		IPv6Address
	};

public:
	/**
	 * \brief Construct a new SocketAddress with no initialized members.
	 */
	SocketAddress();

	/**
	 * \brief Construct a new SocketAddress.
	 */
	SocketAddress(const std::string& destination, uint16_t port = 0);

	/**
	 * \brief Get the remote port.
	 */
	uint16_t port() const
	{
		return m_port;
	}

	/**
	 * \brief Get the address family.
	 */
	AddressFamily family() const
	{
		return m_family;
	}

	/**
	 * Return the remote host in a printable IP-address format.
	 */
	std::string     toIPAddress() const;

	/**
	 * Cast the socket address to a native socket address type (sockaddr).
	 */
	struct sockaddr toNativeType() const;

protected:
	/**
	 * \brief Resolve the remote host and create a native socket address.
	 */
	void resolve();

private:
	uint16_t      m_port;
	address_t     m_address;
	AddressFamily m_family;
	std::string   m_destination;
};

}

}

#endif
