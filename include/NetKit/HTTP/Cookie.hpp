#ifndef __NETKIT_HTTP_COOKIE_HPP
#define __NETKIT_HTTP_COOKIE_HPP

#include <string>
#include <sstream>

namespace NetKit
{

namespace HTTP
{

struct Cookie
{
	std::string host;
	std::string name;
	std::string value;

	std::string toString()
	{
		std::stringstream result;

		result << name << "=" << value;

		return result.str(); 
	};
};

}

}

#endif
