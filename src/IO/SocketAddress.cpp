#include "IO/SocketAddress.hpp"

using namespace NetKit::IO;

SocketAddress::SocketAddress()
{
}

SocketAddress::SocketAddress(const std::string& destination, uint16_t port)
	: m_port(port), m_destination(destination)
{
	resolve();
}

void SocketAddress::resolve()
{
	int result = 0;
	struct addrinfo hints, *results;

	// Zero the whole struct.
	memset(&hints, 0, sizeof(hints));

	hints.ai_protocol = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	// Attempt to resolve the address.
	result = ::getaddrinfo(m_destination.c_str(), "http", &hints, &results);

	// Resolving failed.
	if (result != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));

		return;
	}
	// Resolving was successful.
	else {
		struct addrinfo* ptr = results;

		if (ptr == nullptr)
			return;

		// Check if the address family is AF_INET.
		if (ptr->ai_family == AF_INET) {
			m_family = IPv4Address;

			m_address.sa_in = *reinterpret_cast<struct sockaddr_in*>(ptr->ai_addr);
			m_address.sa_in.sin_port = htons(m_port);
		}
		// It is *most likely* AF_INET6, then.
		else {
			m_family = IPv6Address;

			m_address.sa_in6 = *reinterpret_cast<struct sockaddr_in6*>(ptr->ai_addr);
			m_address.sa_in6.sin6_port = htons(m_port);
		}
	}

	// Clean up our mess.
	freeaddrinfo(results);
}

std::string SocketAddress::toIPAddress() const
{
	if (m_family == IPv4Address) {
		char result[INET_ADDRSTRLEN];

		inet_ntop(AF_INET, &m_address.sa_in.sin_addr, result, INET_ADDRSTRLEN);

		return std::string(result);
	}
	else {
		char result[INET6_ADDRSTRLEN];

		inet_ntop(AF_INET6, &m_address.sa_in6.sin6_addr, result, INET6_ADDRSTRLEN);

		return std::string(result);
	}
}

struct sockaddr SocketAddress::toNativeType() const
{
	if (m_family == IPv4Address) {
		struct sockaddr_in result = m_address.sa_in;

		return *reinterpret_cast<struct sockaddr*>(&result);
	}
	else {
		struct sockaddr_in6 result = m_address.sa_in6;

		return *reinterpret_cast<struct sockaddr*>(&result);
	}
}
