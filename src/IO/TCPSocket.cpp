#include "IO/TCPSocket.hpp"

using namespace NetKit::IO;

TCPSocket::TCPSocket(const std::string& host, uint16_t port)
	: Socket(AF_INET, SOCK_STREAM, 0), m_host(host), m_port(port)
{
}
