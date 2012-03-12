#ifndef __NETKIT_HTTP_COOKIEJAR_HPP
#define __NETKIT_HTTP_COOKIEJAR_HPP
#include <algorithm>
#include "HTTP/Cookie.hpp"

namespace NetKit
{

namespace HTTP
{

/**
 * \brief Cookie container which contains cookies for multiple domains.
 */
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

	/**
	 * \brief Add a cookie with a name and a value.
	 */
	void addCookie(const std::string& name, const std::string& value);

	/**
	 * \brief Access the cookie list by reference.
	 */
	const CookieList& cookies()
	{
		return m_cookies;
	}

	/**
	 * \brief Get a cookie by it's name - works like operator[].
	 */
	const Cookie& getCookieByName(const std::string& name);

	/**
	 * \brief Return a CookieList with cookies for the input domain.
	 */
	CookieList cookiesForDomain(const std::string& domain) const;

	/**
	 * \brief Test to see if there's any cookies for a given domain.
	 */
	bool domainHasCookies(const std::string& domain) const;

private:
	CookieList m_cookies;
};

}

}

#endif
