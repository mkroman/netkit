#include <iostream>
#include <fstream>

#include "NetKit/IO.hpp"

using namespace NetKit;

int main(int argc, char* argv[])
{
	IO::Socket socket(AF_INET, SOCK_STREAM, 0);
	IO::SocketAddress address("www.n.dk", 80);

	std::cout << "Resolved IP is " << address.toIPAddress() << std::endl;

	// if (socket.connect(address)) {
	// 	std::cout << "Connected!" << std::endl;
	// }
	// else {
	// 	std::cout << "Could not connect" << std::endl;
	// }

	return 0;
}
