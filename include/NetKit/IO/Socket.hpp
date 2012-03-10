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
	Socket(int family, int type, int protocol);
	~Socket();

private:
	int           m_fd;
	int           m_type;
	int           m_family;
	int           m_protocol;
	SocketAddress m_address;
};

}

}

#endif
