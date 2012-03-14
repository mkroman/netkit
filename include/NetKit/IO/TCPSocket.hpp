#ifndef __NETKIT_IO_TCPSOCKET_HPP
#define __NETKIT_IO_TCPSOCKET_HPP
#include "IO/Socket.hpp"
#include "IO/Buffer.hpp"

namespace NetKit
{

namespace IO
{

/**
 * \brief Socket wrapper for use in TCP connections.
 */
class TCPSocket : public Socket
{
public:
	TCPSocket();
	/**
	 * \brief Construct a new TCPSocket with a remote host and port.
	 */
	TCPSocket(const std::string& host, uint16_t port);

	/**
	 * \brief Connect to the remote host.
	 */
	bool        connect();

	bool connect(const SocketAddress& socket_address);

	/**
	 * \brief Read until a newline is found and return the entire line.
	 */
	std::string readLine();

	/**
	 * \brief Send a line to the host.
	 */
	void        sendLine(const std::string& line);

private:
	std::string m_host; //!< The remote hostname/ip.
	uint16_t    m_port; //!< The remote port.
	Buffer      m_buffer; //!< Reading buffer.
};

}

}

#endif
