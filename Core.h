#pragma once

// core defines go here

// core includes
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

// Version information
#define E6_VERSION "0.0.1"
#define E6_BUILD_DATE __DATE__ " " __TIME__
#define E6_BUILD_STRING "E6 Version " E6_VERSION " " E6_BUILD_DATE

// MSVC typedefs
#if _MSC_VER
typedef signed __int8 e6_int8;
typedef unsigned __int8 e6_uint8;
typedef signed __int16 e6_int16;
typedef unsigned __int16 e6_uint16;
typedef signed __int32 e6_int32;
typedef unsigned __int32 e6_uint32;
typedef signed __int64 e6_int64;
typedef unsigned __int64 e6_uint64;

#define E6_API __declspec(dllexport)
// GCC typedefs
#elif __GNUC__
typedef __INT8_TYPE__ e6_int8;
typedef __UINT8_TYPE__ e6_uint8;
typedef __INT16_TYPE__ e6_int16;
typedef __UINT16_TYPE__ e6_uint16;
typedef __INT32_TYPE__ e6_int32;
typedef __UINT32_TYPE__ e6_uint32;
typedef __INT64_TYPE__ e6_int64;
typedef __UINT64_TYPE__ e6_uint64;

// we don't use GCC for windows so just define linux here

#define E6_API __attribute__((visibility("default")))
#endif

// OS configuration

#if _WIN32
#define E6_BUILD_WINDOWS
#define E6_BUILD_SDL

// Win32 specific includes
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
// Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  // Needed for getaddrinfo() and freeaddrinfo() 
#include <unistd.h> // Needed for close()

typedef SOCKET int
#endif

