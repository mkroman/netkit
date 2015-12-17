#include "IO/ConnectionManager.hpp"

using namespace NetKit::IO;

ConnectionManager::ConnectionManager()
{
}

template <typename SocketT>
bool ConnectionManager::connect(const std::string& host, uint16_t port)
{
	bool result;

	IO::Connection<SocketT> connection;

	result = connection.connect(host, port);

	m_connections.push_back(&connection);

	return result;
}
