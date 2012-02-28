#include <iostream>
#include <fstream>

#include "netkit/http.hpp"

using namespace NetKit;

int main(int argc, char* argv[])
{
	HTTP::Client client("www.n.dk", 80);
	HTTP::Request request("/login.aspx");
	HTTP::Response* response;

	response = client.get(request);

	request.setPath("/community/login/login.asp");
	request.setBody("username=d&password=d&pdummy=Kode");

	delete response;

	response = client.post(request);

	delete response;

	return 0;
}
