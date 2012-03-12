#include <iostream>
#include "IO/Buffer.hpp"

using namespace NetKit::IO;

Buffer::Buffer()
{
}

void Buffer::add(const char* data, size_t length)
{
	insert(end(), data, data + length);
}

Buffer::size_type Buffer::find(const char byte)
{
	iterator it;

	for (it = begin(); it != end(); it++) {
		if (*it == byte) {
			return std::distance(begin(), it);
		}
	}

	return -1;
}

std::string Buffer::substr(size_type start, size_type end)
{
	std::string result(begin() + start, begin() + end);

	return result;
}

void Buffer::erase(size_type start, size_type end)
{
	deque<unsigned char>::erase(begin() + start, begin() + end);
}
