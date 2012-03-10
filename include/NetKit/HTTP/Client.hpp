#ifndef __NETKIT_HTTP_CLIENT_HPP
#define __NETKIT_HTTP_CLIENT_HPP
#include <string>
#include <cstdint>

#include "HTTP/Cookie.hpp"
#include "HTTP/CookieJar.hpp"

namespace NetKit
{

namespace HTTP
{

class Request;
class Response;

class Client
{
public:
	/**
	 * \brief Construct a new client without a hostname and port.
	 */
	Client();

	/**
	 * \brief Construct a new client associated with a hostname and a port.
	 */
	Client(const std::string& host, uint16_t port);

	/**
	 * \brief Perform a GET request.
	 */
	Response* get(Request& request);

	/**
	 * \brief Perform a PUT request.
	 */
	Response* put(Request& request);

	/**
	 * \brief Perform a POST request.
	 */
	Response* post(Request& request);

	/**
	 * \brief Perform a request where the request method is already set in
	 * the request parameter.
	 */
	Response* request(Request& request);

	/**
	 * Get the cookie jar used in this client.
	 */
	CookieJar& cookieJar()
	{
		return m_cookieJar;
	}

	const Cookie& getCookie(const std::string& name)
	{
		return m_cookieJar.getCookieByName(name);
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
