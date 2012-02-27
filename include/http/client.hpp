#ifndef __HTTP_CLIENT_HPP
#define __HTTP_CLIENT_HPP
#include <string>
#include <cstdint>

namespace HTTP
{

class Request;
class Response;

class Client
{
public:
	Client();
	Client(const std::string& host, uint16_t port);

	Response* get(Request* request);
	Response* put(Request* request);
	Response* post(Request* request);
	Response* request(Request* request);

private:
	int connect();
	size_t readResponseBody(Response* response);
	size_t readResponseHeaders(Response* response);

	int m_socket;
	std::string m_host;
	std::string m_buffer;
	uint16_t m_port;
	uint16_t m_atEOF;
};

}

#endif
