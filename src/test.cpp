#include <iostream>
#include <fstream>

#include "NetKit/IO.hpp"

using namespace NetKit;

int main(int argc, char* argv[])
{
	IO::TCPSocket socket("hhsrv.n.dk", 499);

	if (socket.connect()) {
		std::cout << "Connected!" << std::endl;

		std::string line = socket.readLine();

		std::cout << "<< " << line << std::endl;

		socket.sendLine("dddd");
	}
	else {
		std::cout << "Could not connect" << std::endl;
	}

	return 0;
}
