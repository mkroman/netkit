#ifndef __HTTP_REQUEST_HPP
#define __HTTP_REQUEST_HPP
#include <string>
#include <sstream>
#include <unordered_map>

namespace NetKit
{

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

	const std::string path()
	{
		return m_path;
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
		std::stringstream stringStream;

		stringStream << value;

		m_headers[header] = stringStream.str();
	}

	void setPath(const std::string& path)
	{
		m_path = path;
	}

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
