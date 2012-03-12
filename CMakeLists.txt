PROJECT(NetKit)

SET(CMAKE_BUILD_TYPE Debug)

IF(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=gnu++0x)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(NETKIT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "NETKIT include directory")

SET(NETKIT_SOURCES
	src/HTTP/Client.cpp
	src/HTTP/Cookie.cpp
	src/HTTP/Request.cpp
	src/HTTP/Response.cpp
	src/HTTP/CookieJar.cpp
	src/IO/Socket.cpp
	src/IO/SocketAddress.cpp
	src/IO/TCPSocket.cpp
	src/IO/Buffer.cpp
)

INCLUDE_DIRECTORIES(include include/NetKit)

ADD_LIBRARY(netkit SHARED ${NETKIT_SOURCES})
ADD_EXECUTABLE(test src/test.cpp)
TARGET_LINK_LIBRARIES(test netkit)
