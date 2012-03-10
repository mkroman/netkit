#include "HTTP/CookieJar.hpp"

using namespace NetKit::HTTP;

CookieJar::CookieJar()
{
}

Cookie& CookieJar::operator[](const std::string& name)
{
	auto it = std::find_if(begin(m_cookies), end(m_cookies), [&](Cookie& cookie) {
		return cookie.name() == name;
	});

	return *it;
}

void CookieJar::addCookie(const Cookie& cookie)
{
	m_cookies.push_back(cookie);
}

void CookieJar::addCookie(const std::string& name, const std::string& value)
{
	Cookie cookie(name, value);

	m_cookies.push_back(cookie);
}

const Cookie& CookieJar::getCookieByName(const std::string& name)
{
	auto it = std::find_if(begin(m_cookies), end(m_cookies), [&](Cookie& cookie) {
		return cookie.name() == name;
	});

	return *it;
}

CookieJar::CookieList CookieJar::cookiesForDomain(const std::string& domain) const
{
	CookieList cookies;

	for (auto cookie : m_cookies) {
		if (cookie.domain() == domain) {
			cookies.push_back(cookie);
		}
	}

	return cookies;
}

bool CookieJar::domainHasCookies(const std::string& domain) const
{
	for (auto cookie : m_cookies)
	{
		if (cookie.domain() == domain) {
			return true;
		}
	}

	return false;
}
