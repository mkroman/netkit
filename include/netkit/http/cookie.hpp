#ifndef __NETKIT_HTTP_COOKIE_HPP
#define __NETKIT_HTTP_COOKIE_HPP

#include <string>

namespace NetKit
{

namespace HTTP
{

struct Cookie
{
	std::string host;
	std::string name;
	std::string value;
};

}

}

#endif
