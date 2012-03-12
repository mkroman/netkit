#ifndef __NETKIT_IO_SOCKET_HPP
#define __NETKIT_IO_SOCKET_HPP
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include "IO/SocketAddress.hpp"

namespace NetKit
{

namespace IO
{

class Socket
{
public:
	enum SocketState
	{
		SocketDisconnected,
		SocketTimeout,
		SocketConnected
	};

	/**
	 * \brief Construct a new socket, the parameters are the exact same as the regular
	 * ::socket function.
	 */
	Socket(int family, int type, int protocol);

	/**
	 * \brief Clean up the socket on destruction.
	 */
	~Socket();

	/**
	 * \brief Attempt to establish a connection through the socket \c address.
	 *
	 * \returns True if successful.
	 */
	bool connect(const SocketAddress& address);

	/**
	 * \brief Write a number of bytes to the socket file descriptor.
	 *
	 * \returns The number of bytes written, or 0 if closed, -1 if failed.
	 */
	ssize_t write(const char* source, size_t length);

	/**
	 * \brief Read a number of bytes from the socket file descriptor.
	 *
	 * \returns The number of bytes read into \c destination.
	 */
	ssize_t read(char* destination, size_t length);

	/**
	 * \brief Get the socket file descriptor.
	 */
	const int fd()
	{
		return m_fd;
	}

	/**
	 * \brief Test to see if the socket is connected.
	 */
	bool connected()
	{
		return (m_state == SocketConnected);
	}

protected:
	/**
	 * \brief Called when the connection was lost.
	 */
	void connectionLost();

private:
	int           m_fd;
	int           m_type;
	int           m_family;
	int           m_protocol;
	SocketState   m_state;
	SocketAddress m_address;
};

}

}

#endif
