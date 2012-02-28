#ifndef __HTTP_RESPONSE_HPP
#define __HTTP_RESPONSE_HPP
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

namespace HTTP
{

class Response
{
public:
	Response();

	int code() const
	{
		return m_code;
	}

	const std::string& body() const
	{
		return m_body;
	}
	
	const std::string& status() const
	{
		return m_status;
	}

	const std::string& header(const std::string& header)
	{
		if (m_headers.count(header) == 1) {
			return m_headers[header];
		}
		else {
			throw std::invalid_argument("No such header");
		}
	}

	bool hasHeader(const std::string& header)
	{
		return (m_headers.count(header) == 1);
	}

	void setBody(const std::string& body)
	{
		m_body = body;
	}

	void setCode(int code)
	{
		m_code = code;
	}

	void setStatus(const std::string& status)
	{
		m_status = status;
	}

	void setHeader(const std::string& header, const std::string& value)
	{
		m_headers[header] = value;
	}

	void save(const std::string& path);

private:
	int m_code;
	std::string m_body;
	std::string m_status;
	std::map<std::string, std::string> m_headers;
};

}

#endif
