#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>
#include <cstddef>

#include "http.hpp"
#include "http/client.hpp"
#include "http/request.hpp"
#include "http/response.hpp"

using namespace HTTP;

Client::Client()
{

}

Client::Client(const std::string& host, uint16_t port)
	: m_host(host), m_port(port)
{

}

Response* Client::get(Request* request)
{
	request->setMethod(Request::GET);

	return this->request(request);
}

Response* Client::put(Request* request)
{
	request->setMethod(Request::PUT);

	return this->request(request);
}

Response* Client::post(Request* request)
{
	request->setMethod(Request::POST);

	return this->request(request);
}

Response* Client::request(Request* request)
{
	int result;
	std::string requestBody, requestHeaders;

	// Create a socket and establish connection.
	result = connect();

	if (result < 0) {
		perror("Unable to connect");

		return nullptr;
	}
	else {
		m_socket = result;
		m_atEOF = 0;
	}

	// Build headers.
	switch (request->method())
	{
		default:
		case HTTP::Request::GET:
		{
			requestHeaders += "GET " + request->path() + " HTTP/1.1\r\n";

			break;
		}

		case HTTP::Request::PUT:
		{
			requestHeaders += "PUT " + request->path() + "\r\n";

			request->setHeader("Content-Length", request->body().length());

			break;
		}

		case HTTP::Request::POST:
		{
			requestHeaders += "POST " + request->path() + " HTTP/1.1\r\n";

			request->setHeader("Content-Type", "application/x-www-form-urlencoded");
			request->setHeader("Content-Length", request->body().length());

			break;
		}

		case HTTP::Request::DELETE:
		{
			requestHeaders += "DELETE " + request->path() + " HTTP/1.1\r\n";

			break;
		}
	}

	// Add mandatory Host header.
	requestHeaders += "Host: " + m_host + "\r\n";

	// Add headers.
	for (auto header : request->headers())
	{
		requestHeaders += header.first + ": " + header.second + "\r\n";
	}

	requestHeaders += "\r\n";

	// Actually send the headers.
	::send(m_socket, requestHeaders.c_str(), requestHeaders.length(), MSG_PEEK);

	// Start working on the body.
	requestBody = request->body();

	// Send content body if this is a POST/PUT request.
	if (request->method() == HTTP::Request::POST || request->method() == HTTP::Request::PUT) {
		::send(m_socket, requestBody.c_str(), requestBody.length(), MSG_PEEK);
	}

	Response* response = new Response();

	// Read and parse the response headers.
	result = readResponseHeaders(response);

	// Parsing failed.
	if (result < 0) {
		perror("Could not read response headers");

		return nullptr;
	}

	// Read and parse the response body if there's still something to read.
	if (m_atEOF == 0) {
		result = readResponseBody(response);
	}

	return response;
}

size_t Client::readResponseHeaders(Response* response)
{
	char buffer[512];
	std::string headers;
	size_t size = 0, total = 0, pointer;

	size = ::recv(m_socket, buffer, 512, 0);

	m_buffer.append(buffer, size);

	while (size > 0) {
		pointer = m_buffer.find("\r\n\r\n");

		if (pointer != std::string::npos) {
			pointer += 4;
			headers = m_buffer.substr(0, pointer - 4);

			if (m_buffer.length() > pointer) {
				m_buffer.erase(0, pointer);

				break;
			}
			else {
				m_buffer.clear();

				break;
			}
		}

		size = ::recv(m_socket, buffer, 512, 0);
		total += size;

		m_buffer.append(buffer, size);
	}

	if (size < 0) {
		perror("recv failed");
	}
	else if (size == 0) {
		m_atEOF = 1;
	}

	// Start parsing the headers.
	std::string line;
	pointer = headers.find_first_of("\r\n");

	while (pointer != std::string::npos) {
		line = headers.substr(0, pointer);
		size = line.find_first_of(":");

		if (size != std::string::npos) {
			response->setHeader(line.substr(0, size), line.substr(size + 2, pointer));
		}
		else {
			int code;
			char version[3], status[128];

			sscanf(line.substr(0, pointer).c_str(), "HTTP/%s %d %s", &version, &code, &status);

			response->setCode(code);
			response->setStatus(status);
		}

		headers.erase(0, pointer + 2);

		pointer = headers.find_first_of("\r\n");		
	}

	return total;
}

size_t Client::readResponseBody(Response* response)
{
	char* buffer = new char[1024];
	size_t size = 0, total = 0, pointer = 0;

	size = ::recv(m_socket, buffer, 1024, 0);
	total += size;

	while (size > 0) {
		total += size;
		m_buffer.append(buffer, size);

		size = ::recv(m_socket, buffer, 1024, 0);
	}

	m_atEOF = 1;

	response->setBody(m_buffer);
	m_buffer.clear();

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
