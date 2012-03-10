
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
	/**
	 * \brief Create a socket, resolve the hostname and connect to the host.
	 */
	int connect();

	/**
	 * \brief Parse a header with cookie values in it.
	 */
	void parseCookieHeader(const std::string& line);

	/**
	 * \brief Parse the response body as it's getting received.
	 */
	size_t readResponseBody(Response* response);

	/**
	 * \brief Parse the response headers.
	 */
	size_t readResponseHeaders(Response* response);

	int         m_socket; //!< The socket file descriptor.
	uint16_t    m_port; //!< The remote host.
	uint16_t    m_atEOF; //!< Flag that tells if the socket is open or not.
	std::string m_host; //!< The remote host address/hostname.
	std::string m_buffer; //!< The i/o buffer.
	CookieJar   m_cookieJar; //!< The cookie jar to hold the cookies.
};

}

}

#endif
