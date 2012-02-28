#ifndef __NETKIT_HTTP_COOKIEJAR_HPP
#define __NETKIT_HTTP_COOKIEJAR_HPP

#include <algorithm>

#include "http/cookie.hpp"

namespace NetKit
{

namespace HTTP
{

class CookieJar
{
public:
	CookieJar();

	Cookie& operator[](const std::string& name)
	{
		auto iterator = std::find_if(begin(m_cookies), end(m_cookies), [&](Cookie& cookie) {
			return cookie.name == name;
		});

		if (iterator != end(m_cookies))
		{
			return *iterator;
		}
		else
		{
			return addCookie(name, "");
		}
	}

	const Cookie& getCookie(const std::string& name)
	{
		auto iterator = std::find_if(begin(m_cookies), end(m_cookies), [&](Cookie& cookie) {
			return cookie.name == name;
		});

		return *iterator;
	}

	Cookie& addCookie(const Cookie& cookie)
	{
		m_cookies.push_back(cookie);

		return m_cookies.back();
	}

	Cookie& addCookie(const std::string& name, const std::string& value)
	{
		Cookie cookie;

		cookie.name = name;
		cookie.value = value;

		m_cookies.push_back(cookie);

		return m_cookies.back();
	}

	bool domainHasCookies(const std::string& domain)
	{
		auto it = std::find_if(begin(m_cookies), end(m_cookies), [&](Cookie& cookie) {
			return cookie.host == domain;
		});

		return (it != end(m_cookies));
	}

	const std::string headerForDomain(const std::string& host)
	{
		std::string result;

		for (auto cookie : m_cookies)
		{
			if (cookie.host == host)
			{
				result += cookie.name + "=" + cookie.value + "; ";
			}
		}

		if (!result.empty())
		{
			result.resize(result.size() - 2);
		}

		return result;
	}

private:
	std::vector<Cookie> m_cookies;
};

}

}

#endif
