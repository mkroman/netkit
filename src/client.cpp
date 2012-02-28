#include <cstring>
#include <sstream>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "http.hpp"
#include "http/client.hpp"
#include "http/request.hpp"
#include "http/response.hpp"

using namespace NetKit::HTTP;

Client::Client()
{
}

Client::Client(const std::string& host, uint16_t port)
	: m_host(host), m_port(port)
{
}

Response* Client::get(Request& request)
{
	request.setMethod(Request::GET);

	return this->request(request);
}

Response* Client::put(Request& request)
{
	request.setMethod(Request::PUT);

	return this->request(request);
}

Response* Client::post(Request& request)
{
	request.setMethod(Request::POST);

	return this->request(request);
}

Response* Client::request(Request& request)
{
	int result;
	std::string requestBody, requestHeaders;

	// Create a socket and establish connection.
	result = connect();

	if (result < 0)
	{
		perror("Unable to connect");

		return nullptr;
	}
	else
	{
		m_socket = result;
		m_atEOF = 0;
	}

	// Build headers.
	switch (request.method())
	{
		default:
		case HTTP::Request::GET:
		{
			requestHeaders += "GET " + request.path() + " HTTP/1.1\r\n";

			break;
		}

		case HTTP::Request::PUT:
		{
			requestHeaders += "PUT " + request.path() + "\r\n";

			request.setHeader("Content-Length", request.body().length());

			break;
		}

		case HTTP::Request::POST:
		{
			requestHeaders += "POST " + request.path() + " HTTP/1.1\r\n";

			request.setHeader("Content-Type", "application/x-www-form-urlencoded");
			request.setHeader("Content-Length", request.body().length());

			break;
		}

		case HTTP::Request::DELETE:
		{
			requestHeaders += "DELETE " + request.path() + " HTTP/1.1\r\n";

			break;
		}
	}

	// Add mandatory Host header.
	requestHeaders += "Host: " + m_host + "\r\n";

	// Add headers.
	for (auto header : request.headers())
	{
		requestHeaders += header.first + ": " + header.second + "\r\n";
	}

	requestHeaders += "User-Agent: ";
	requestHeaders += kUserAgentHeader;
	requestHeaders += "\r\n";
	requestHeaders += "Connection: close\r\n";

	requestHeaders += "\r\n";

	// Actually send the headers.
	::send(m_socket, requestHeaders.c_str(), requestHeaders.length(), MSG_PEEK);

	// Start working on the body.
	requestBody = request.body();

	// Send content body if this is a POST/PUT request.
	if (request.method() == HTTP::Request::POST || request.method() == HTTP::Request::PUT)
	{
		::send(m_socket, requestBody.c_str(), requestBody.length(), 0);
	}

	Response* response = new Response();

	// Read and parse the response headers.
	result = readResponseHeaders(response);

	// Parsing failed.
	if (result < 0)
	{
		perror("Could not read response headers");

		delete response;
		return nullptr;
	}

	// Read and parse the response body if there's still something to read.
	if (!m_atEOF)
	{
		result = readResponseBody(response);
	}

	::close(m_socket);

	return response;
}

size_t Client::readResponseHeaders(Response* response)
{
	size_t size = 0, sum = 0, pointer;
	char buffer[kHTTPBufferSize];
	std::string headers;

	size = recv(m_socket, buffer, kHTTPBufferSize, 0);
	m_buffer.append(buffer, size);

	while (size > 0)
	{
		pointer = m_buffer.find("\r\n\r\n");

		if (pointer != std::string::npos)
		{
			headers = m_buffer.substr(0, pointer);

			m_buffer.erase(0, (pointer + 4));

			break;
		}

		size = recv(m_socket, buffer, 512, 0);
		sum += size;

		m_buffer.append(buffer, size);
	}

	if (size < 0)
	{
		perror("Reading failed");
	}
	else if (size == 0)
	{
		m_atEOF = 1;
	}

	// Start parsing the headers.
	std::string line;

	pointer = headers.find("\r\n");

	while (pointer != std::string::npos)
	{
		line = headers.substr(0, pointer);
		size = line.find(":");

		if (size != std::string::npos)
		{
			response->setHeader(line.substr(0, size), line.substr(size + 2, pointer));
		}
		else
		{
			int code;
			char version[3], status[128];

			sscanf(line.substr(0, pointer).c_str(), "HTTP/%s %d %s", &version, &code, &status);

			response->setCode(code);
			response->setStatus(status);
		}

		headers.erase(0, pointer + 2);
		pointer = headers.find("\r\n");		
	}

	return sum;
}

size_t Client::readResponseBody(Response* response)
{
	char* buffer = new char[1024];
	size_t size = 0, total = 0, pointer = 0, contentLength = 0;

	if (response->hasHeader("Content-Length"))
	{
		std::stringstream stream;

		stream << response->header("Content-Length");
		stream >> contentLength;
	}
	
	do
	{
		size = ::recv(m_socket, buffer, 1024, 0);
		total += size;

		if (contentLength != 0 && total >= contentLength)
		{
			m_buffer.append(buffer, size - (contentLength - total));

			break;
		}
		else
		{
			m_buffer.append(buffer, size);
		}
	}
	while (size > 0);

	m_atEOF = 1;

	response->setBody(m_buffer);
	m_buffer.clear();

	delete [] buffer;

	return total;
}

int Client::connect()
{
	int result, socket;
	struct hostent* remote_host;
	struct sockaddr_in remote_addr;

	memset(&remote_addr, 0, sizeof(struct sockaddr_in));

	socket = ::socket(AF_INET, SOCK_STREAM, 0);
	remote_host = gethostbyname(m_host.c_str());

	if (socket < 0 || !remote_host)
		return -1;

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(m_port);

	memcpy(&remote_addr.sin_addr, remote_host->h_addr, remote_host->h_length);

	result = ::connect(socket, (struct sockaddr*)&remote_addr, sizeof(struct sockaddr));

	if (result < 0)
		return -1;
	else
		return socket;
}
