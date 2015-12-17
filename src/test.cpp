#include <iostream>
#include <fstream>
#include <vector>

#include "NetKit/IO.hpp"

using namespace NetKit;

int main(int argc, char* argv[])
{
	IO::Connection<IO::TCPSocket> connection;
	IO::ConnectionManager manager;

	if (manager.connect(&connection)) {
		
	}

	return 0;
}
