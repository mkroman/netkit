#ifndef __HTTP_REQUEST_HPP
#define __HTTP_REQUEST_HPP
#include <string>
#include <sstream>
#include <unordered_map>

namespace NetKit
{

namespace HTTP
{

/**
 * \brief Request to be processed by the client.
 */
class Request
{
public:
	enum RequestMethod
	{
		GET,
		PUT,
		POST,
		DELETE
	};

	/**
	 * \brief Construct a request without a request path.
	 */
	Request();

	/**
	 * \brief Construct a request with a request path.
	 */
	Request(const std::string& path);

	/**
	 * \brief Get the request path.
	 */
	const std::string path()
	{
		return m_path;
	}

	/**
	 * \brief Get the request body.
	 */
	const std::string& body()
	{
		return m_body;
	}

	/**
	 * \brief Get the request method.
	 */
	RequestMethod method() const
	{
		return m_method;
	}

	/**
	 * \brief Get the request headers.
	 */
	std::unordered_map<std::string, std::string>& headers()
	{
		return m_headers;
	}

	/**
	 * \brief Set the request method.
	 */
	void setMethod(RequestMethod method)
	{
		m_method = method;
	}

	/**
	 * \brief Set a request header.
	 */
	void setHeader(const std::string& header, const std::string& value)
	{
		m_headers[header] = value;
	}

	/**
	 * \brief Set a request header to a numeric value.
	 */
	void setHeader(const std::string& header, const size_t value)
	{
		std::stringstream stringStream;

		stringStream << value;

		m_headers[header] = stringStream.str();
	}

	/**
	 * \brief Set the request path.
	 */
	void setPath(const std::string& path)
	{
		m_path = path;
	}

	/**
	 * \brief Set the request body.
	 */
	void setBody(const std::string& body)
	{
		m_body = body;
	}

private:
	std::string m_path;
	std::string m_body;
	RequestMethod m_method;
	std::unordered_map<std::string, std::string> m_headers;
};

}

}

#endif
