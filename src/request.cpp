#include "http.hpp"
#include "http/request.hpp"

using namespace HTTP;

Request::Request()
{
}

Request::Request(const std::string& path)
	: m_path(path)
{
}
