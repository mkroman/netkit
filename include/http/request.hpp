#ifndef __HTTP_REQUEST_HPP
#define __HTTP_REQUEST_HPP
#include <string>
#include <unordered_map>

namespace HTTP
{

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

	Request();
	Request(const std::string& path);

	void setMethod(RequestMethod method)
	{
		m_method = method;
	}

	void setHeader(const std::string& header, const std::string& value)
	{
		m_headers[header] = value;
	}

	void setHeader(const std::string& header, const size_t value)
	{
		char buffer[32];
		size_t size;

		size = sprintf(buffer, "%d", value);

		m_headers[header] = std::string(buffer, size);
	}

	void setBody(const std::string& body)
	{
		m_body = body;
	}

	const std::string& body()
	{
		return m_body;
	}

	RequestMethod method() const
	{
		return m_method;
	}

	std::unordered_map<std::string, std::string>& headers()
	{
		return m_headers;
	}

	const std::string path()
	{
		return m_path;
	}

private:
	std::string m_body;
	std::string m_path;
	RequestMethod m_method;
	std::unordered_map<std::string, std::string> m_headers;
};

}

#endif
