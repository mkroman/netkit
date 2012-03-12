#ifndef __NETKIT_IO_TCPSOCKET_HPP
#define __NETKIT_IO_TCPSOCKET_HPP
#include "IO/Socket.hpp"
#include "IO/Buffer.hpp"

namespace NetKit
{

namespace IO
{

class TCPSocket : public Socket
{
public:
	TCPSocket(const std::string& host, uint16_t port);

	bool        connect();
	std::string readLine();
	void        sendLine(const std::string& line);

private:
	std::string m_host;
	uint16_t    m_port;
	Buffer      m_buffer;
};

}

}

#endif
