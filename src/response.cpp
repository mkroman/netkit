#include <fstream>
#include "http/response.hpp"

using namespace HTTP;

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
