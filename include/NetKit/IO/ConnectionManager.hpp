#ifndef __NETKIT_IO_CONNECTIONMANAGER_HPP
#define __NETKIT_IO_CONNECTIONMANAGER_HPP
#include <string>
#include <vector>
#include "Connection.hpp"

namespace NetKit
{

namespace IO
{

class ConnectionManager
{
public:
	ConnectionManager();

	template <typename SocketT>
	bool connect(const std::string& host, uint16_t port);

protected:
	std::vector<IO::ConnectionBase*> m_connections;
};

}

}

#endif
