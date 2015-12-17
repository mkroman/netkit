#ifndef __NETKIT_IO_CONNECTION_HPP
#define __NETKIT_IO_CONNECTION_HPP
#include <event.h>
#include <string>
#include "IO/SocketAddress.hpp"

namespace NetKit
{

namespace IO
{

struct IOBuffer
{
	IOBuffer()
	{
		read = evbuffer_new();
		write = evbuffer_new();
	}

	~IOBuffer()
	{
		evbuffer_free(read);
		evbuffer_free(write);
	}

	struct evbuffer* read;
	struct evbuffer* write;
};

class ConnectionBase
{
public:
	virtual bool connect(const std::string& host, uint16_t port) {}

protected:
	IOBuffer m_buffer;
};

template <typename SocketT>
class Connection : public ConnectionBase
{
public:
	Connection();
	
	bool connect(const std::string& host, uint16_t port);

protected:
	SocketT m_socket;
};

template <class T>
Connection<T>::Connection()
{
}

template <class T>
bool Connection<T>::connect(const std::string& host, uint16_t port)
{
	SocketAddress address(host, port);

	return m_socket.connect(address);
}

}

}

#endif
