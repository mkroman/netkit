#ifndef __NETKIT_HTTP_COOKIE_HPP
#define __NETKIT_HTTP_COOKIE_HPP

#include <string>
#include <sstream>

namespace NetKit
{

namespace HTTP
{

/**
 * \brief Cookie container class.
class Cookie
{
public:
	/**
	 * \brief Construct a cookie with no name, value or domain.
	 */
	Cookie();

	/**
	 * \brief Construct a cookie with a name and a value.
	 */
	Cookie(const std::string& name, const std::string& value);

	/**
	 * \brief Get the cookie formatted as a string.
	 */
	std::string toString() const;

	/**
	 * \brief Get the cookie name.
	 */
	const std::string& name()
	{
		return m_name;
	}

	/**
	 * \brief Get the cookie value.
	 */
	const std::string& value()
	{
		return m_value;
	}

	/**
	 * \brief Get the cookie domain.
	 */
	const std::string& domain()
	{
		return m_domain;
	}

	/**
	 * \brief Set the cookie name.
	 */
	void setName(const std::string& name)
	{
		m_name = name;
	}

	/**
	 * \brief Set the cookie value.
	 */
	void setValue(const std::string& value)
	{
		m_value = value;
	}

	/**
	 * \brief Set the cookie domain.
	 */
	 void setDomain(const std::string& domain)
	 {
	 	m_domain = domain;
	 }

private:
	std::string m_name;
	std::string m_value;
	std::string m_domain;
};

}

}

#endif
