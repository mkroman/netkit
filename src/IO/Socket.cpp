#include "IO/Socket.hpp"

using namespace NetKit::IO;

Socket::Socket(int family, int type, int protocol)
	: m_family(family), m_type(type), m_protocol(protocol), m_state(SocketDisconnected)
{
	int result = 0;

	result = ::socket(family, type, protocol);

	if (result <= 0) {
		throw std::runtime_error("Could not create socket file descriptor.");
	}
	else {
		m_fd = result;
	}
}

Socket::~Socket()
{
	::close(m_fd);
}

bool Socket::connect(const SocketAddress& address)
{
	int result = 0;
	struct sockaddr native = address.toNativeType();

	result = ::connect(m_fd, &native, sizeof(native));

	if (result == 0) {
		m_state = SocketConnected;
	}

	return (result == 0);
}

ssize_t Socket::write(const char* source, size_t length)
{
	ssize_t result = 0;

	result = ::send(m_fd, source, length, 0);

	return result;
}

ssize_t Socket::read(char* destination, size_t length)
{
	ssize_t result = 0;

	result = ::recv(m_fd, destination, length, 0);

	return result;
}

void Socket::connectionLost()
{
	m_state = SocketDisconnected;
}
