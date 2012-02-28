#include <iostream>
#include <fstream>
#include "http.hpp"

int main(int argc, char* argv[])
{
	HTTP::Client client("www.n.dk", 80);
	HTTP::Request request("/login.aspx");
	HTTP::Response* response;

	request.setBody("username=functor&password=V0IR1RWW&pdummy=Kode");

	response = client.get(request);

	// if (response->code() == 302) {
	// 	request.setPath(response->header("Location"));
	// 	request.setHeader("Cookie", response->header("Set-Cookie"));

	// 	delete response;

	// 	response = client.get(request);
	// }

	if (response->code() == 302) {
		std::string cookie = response->header("Set-Cookie");

		delete response;

		request.setPath("/community/login/login.asp");
		request.setHeader("Cookie", cookie);

		response = client.post(request);

		if (response->code() == 200) {
			std::cout << "yay!" << std::endl;

			std::cout << response->body() << std::endl;
		}
	}
	
	delete response;

	return 0;
}
