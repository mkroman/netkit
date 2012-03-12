#ifndef __HTTP_RESPONSE_HPP
#define __HTTP_RESPONSE_HPP
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

namespace NetKit
{

namespace HTTP
{

/**
 * \brief HTTP response that gets returned on request.
 *
 * \note Does not delete itself!
 */
class Response
{
public:
	Response();

	/**
	 * \brief Get the numeric response code.
	 */
	int code() const
	{
		return m_code;
	}

	/**
	 * \brief Get the response body.
	 */
	const std::string& body() const
	{
		return m_body;
	}
	
	/**
	 * \brief Get the response string.
	 */
	const std::string& status() const
	{
		return m_status;
	}

	/**
	 * \brief Get the value of a response header.
	 */
	const std::string& header(const std::string& header)
	{
		if (m_headers.count(header) == 1)
		{
			return m_headers[header];
		}
		else
		{
			throw std::invalid_argument("No such header");
		}
	}

	/**
	 * \brief Test to see if the response has a header with a specific name.
	 */
	bool hasHeader(const std::string& header)
	{
		return (m_headers.count(header) == 1);
	}

	/**
	 * \brief Set the response body.
	 */
	void setBody(const std::string& body)
	{
		m_body = body;
	}

	/**
	 * \brief Set the response code.
	 */
	void setCode(int code)
	{
		m_code = code;
	}

	/**
	 * \brief Set the response status.
	 */
	void setStatus(const std::string& status)
	{
		m_status = status;
	}

	/**
	 * \brief Set a response header.
	 */
	void setHeader(const std::string& header, const std::string& value)
	{
		m_headers[header] = value;
	}

	/**
	 * \brief Save the response body to a file.
	 */
	void save(const std::string& path);

private:
	int m_code; //!< The response code.
	std::string m_body; //!< The response body.
	std::string m_status; //!< The response status.
	std::map<std::string, std::string> m_headers; //!< The response headers.
};

}

}

#endif
