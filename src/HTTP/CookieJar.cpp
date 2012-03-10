#include "HTTP/CookieJar.hpp"

using namespace NetKit::HTTP;

CookieJar::CookieJar()
{
}

Cookie& CookieJar::operator[](const std::string& name)
{
	auto it = std::find_if(begin(m_cookies), end(m_cookies), [&](Cookie& cookie) {
		return cookie.name == name;
	});

	return *it;
}

void CookieJar::addCookie(const Cookie& cookie)
{
	m_cookies.push_back(cookie);
}

void CookieJar::addCookie(const std::string& name, const std::string& value)
{
	Cookie cookie;

	cookie.name = name;
	cookie.value = value;

	m_cookies.push_back(cookie);
}
