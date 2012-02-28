#ifndef __NETKIT_HTTP_CLIENT_HPP
#define __NETKIT_HTTP_CLIENT_HPP
#include <string>
#include <cstdint>

#include "http/cookie.hpp"
#include "http/cookiejar.hpp"

namespace NetKit
{

namespace HTTP
{

class Request;
class Response;

class Client
{
public:
	Client();
	Client(const std::string& host, uint16_t port);

	Response* get(Request& request);
	Response* put(Request& request);
	Response* post(Request& request);
	Response* request(Request& request);

	CookieJar& cookies()
	{
		return m_cookieJar;
	}

	CookieJar& cookieJar()
	{
		return m_cookieJar;
	}

	const Cookie& getCookie(const std::string& name)
	{
		return m_cookieJar.getCookie(name);
	}

private:
	int connect();
	void parseCookieHeader(const std::string& line);
	size_t readResponseBody(Response* response);
	size_t readResponseHeaders(Response* response);

	int m_socket;
	uint16_t m_port;
	uint16_t m_atEOF;
	std::string m_host;
	std::string m_buffer;
	CookieJar m_cookieJar;
};

}

}

#endif
