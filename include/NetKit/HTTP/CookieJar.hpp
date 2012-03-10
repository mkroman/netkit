#ifndef __NETKIT_HTTP_COOKIEJAR_HPP
#define __NETKIT_HTTP_COOKIEJAR_HPP
#include <algorithm>
#include "HTTP/Cookie.hpp"

namespace NetKit
{

namespace HTTP
{

class CookieJar
{
public:
	typedef std::vector<Cookie> CookieList;

	/**
	 * \brief Instantiate a cookie jar.
	 */
	CookieJar();

	/**
	 * \brief Get a cookie by its name.
	 */
	Cookie& operator[](const std::string& name);
	
	/**
	 * \brief Add a cookie instance.
	 */
	void addCookie(const Cookie& cookie);

	/*
	 * \brief Add a cookie with a name and a value.
	 */
	void addCookie(const std::string& name, const std::string& value);

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
	CookieList m_cookies;
};

}

}

#endif
