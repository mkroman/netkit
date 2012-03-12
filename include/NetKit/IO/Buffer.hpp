#ifndef __NETKIT_IO_BUFFER_HPP
#define __NETKIT_IO_BUFFER_HPP
#include <deque>
#include <string>
#include <iterator>

namespace NetKit
{

namespace IO
{

using std::deque;

class Buffer : private deque<unsigned char>
{
public:
	Buffer();

	/**
	 * \brief Append a data segment to the buffer.
	 */
	void add(const char* data, size_type length);

	/**
	 * \brief Find an instance of a byte.
	 */
	size_type find(const char byte);

	/**
	 * \brief Take a chunk and return it as a string.
	 */
	std::string substr(size_type start, size_type end);

	/**
	 * \brief Erase a segment from the buffer.
	 */
	void erase(size_type start, size_type end);
};

}

}

#endif
