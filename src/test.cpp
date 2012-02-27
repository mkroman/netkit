#include <iostream>
#include <fstream>
#include "http.hpp"

int main(int argc, char* argv[])
{
	std::ofstream file("/home/mk/test.tar.gz");

	HTTP::Client* client = new HTTP::Client("cycle.io", 80);
	HTTP::Request* request = new HTTP::Request("/Babble.js.tar.gz");
	HTTP::Response* response;

	request->setBody("balls");
	request->setHeader("User-Agent", "Mozilla/5.0");

	response = client->get(request);

	delete client;
	delete request;
	delete response;

	return 0;
}
