#include <iostream>
#include <fstream>
#include <vector>

#include "NetKit/IO.hpp"

using namespace NetKit;

int main(int argc, char* argv[])
{
	IO::Connection<IO::TCPSocket> connection;

	connection.connect("hhsrv.n.dk", 499);

	std::vector<IO::Connection*> connections;

	connections.push_back(&connection);

	return 0;
}
