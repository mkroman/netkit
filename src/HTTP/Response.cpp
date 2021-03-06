#include <fstream>
#include "HTTP/Response.hpp"

using namespace NetKit::HTTP;

Response::Response()
	: m_body()
{
}

void Response::save(const std::string& path)
{
	std::ofstream file(path);

	if (file.is_open())
	{
		file.write(m_body.c_str(), m_body.size());
		file.close();
	}
}
