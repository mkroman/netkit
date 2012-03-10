#include "IO/Socket.hpp"

using namespace NetKit::IO;

Socket::Socket(int family, int type, int protocol)
	: m_family(family), m_type(type), m_protocol(protocol)
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
