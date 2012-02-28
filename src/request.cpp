#include "http.hpp"
#include "http/request.hpp"

using namespace NetKit::HTTP;

Request::Request()
{
}

Request::Request(const std::string& path)
	: m_path(path)
{
}
