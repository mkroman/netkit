#ifndef __NETKIT_IO_CONNECTION_HPP
#define __NETKIT_IO_CONNECTION_HPP
#include <event.h>

namespace NetKit
{

namespace IO
{

template <typename SocketT>
class Connection
{
public:
	~Connection();


private:
	T m_socket;
	struct evbuffer m_readBuffer;
	struct evbuffer m_writeBuffer;
};

}

}

#endif
