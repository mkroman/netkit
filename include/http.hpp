#ifndef __HTTP_HPP
#define __HTTP_HPP
#include "http/client.hpp"
#include "http/request.hpp"
#include "http/response.hpp"

#define kHTTPBufferSize 512

namespace HTTP
{
	static const char DefaultUserAgent[] = "Mozilla/5.0";
}

#endif
