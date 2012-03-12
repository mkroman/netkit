#include "IO/TCPSocket.hpp"

using namespace NetKit::IO;

TCPSocket::TCPSocket(const std::string& host, uint16_t port) : Socket(AF_INET, SOCK_STREAM, 0),
	m_host(host), m_port(port)
{
}

bool TCPSocket::connect()
{
	SocketAddress address(m_host, m_port);

	return Socket::connect(address);
}

std::string TCPSocket::readLine()
{
	char data[512];
	size_t size = 0, index = -1;
	std::string result;

	while (index == std::string::npos) {
		size = read(data, 512);

		if (size > 0) {
			m_buffer.add(data, size);
			index = m_buffer.find('\n');
		}
		else {
			connectionLost();
		}
	}

	result = m_buffer.substr(0, index);
	m_buffer.erase(0, index + 1);

	return result;
}

void TCPSocket::sendLine(const std::string& line)
{
	ssize_t size = 0;
	std::string copy(line);

	if (copy[copy.length() - 1] != '\n') {
		copy.append("\n");
	}

	size = write(copy.c_str(), copy.length());

	if (size <= 0)
		connectionLost();
}
