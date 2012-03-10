#ifndef __HTTP_HPP
#define __HTTP_HPP

#include "HTTP/Client.hpp"
#include "HTTP/Request.hpp"
#include "HTTP/Response.hpp"

#define kHTTPBufferSize 512

namespace NetKit
{

/**
 * HTTP Client library.
 *
 * Currently supported methods: GET, PUT, POST and DELETE.
 * The client tries to support HTTP 1.1 technologies as much as possible.
 */
namespace HTTP
{

static const char kUserAgentHeader[] = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11";

}

}

#endif
