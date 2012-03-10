#include "HTTP/Cookie.hpp"

using namespace NetKit::HTTP;

Cookie::Cookie()
{
}

Cookie::Cookie(const std::string& name, const std::string& value)
	: m_name(name), m_value(value)
{
}

std::string Cookie::toString() const
{
	return m_name + "=" + m_value;
}
