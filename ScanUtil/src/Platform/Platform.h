#ifndef __SCAN_PLATFORM_PLATFORM_H__
#define __SCAN_PLATFORM_PLATFORM_H__


#if defined(_WIN64)
	#define SCAN_WINDOWS_PLATFORM 1
	#define SCAN_PLATFORMX64 1
#elif defined(_WIN32)
	#define SCAN_WINDOWS_PLATFORM 1
	#define SCAN_PLATFORMX32 1
#else
	#define SCAN_WINDOWS_PLATFORM 0
#endif


#if defined(__linux__)
#define SCAN_LINUX_PLATFORM 1
#else
#define SCAN_LINUX_PLATFORM 0
#endif


#if defined(__APPLE__)
#define SCAN_APPLE_PLATFORM 1
#else
#define SCAN_APPLE_PLATFORM 0
#endif


#if !defined(SCAN_PLATFORMX32) && !defined(SCAN_PLATFORMX64)
#define SCAN_PLATFORMX32 (SB::Platform::Details::GIs32BitsEnvironment)
#define SCAN_PLATFORMX64 !(SCAN_PLATFORMX32)
#endif


namespace SB::Platform::Details
{
	// Checks at compile time if an environment is 32 bits.
	constexpr bool GIs32BitsEnvironment = sizeof(nullptr) == 4;
}

#include "Types.h"

#define DECLARE_PLATFORM_TYPE(type) using SB::Platform::Types::type


DECLARE_PLATFORM_TYPE(int8);
DECLARE_PLATFORM_TYPE(int16);
DECLARE_PLATFORM_TYPE(int32);
DECLARE_PLATFORM_TYPE(int64);

DECLARE_PLATFORM_TYPE(uint8);
DECLARE_PLATFORM_TYPE(uint16);
DECLARE_PLATFORM_TYPE(uint32);
DECLARE_PLATFORM_TYPE(uint64);

DECLARE_PLATFORM_TYPE(SIZE_T);

DECLARE_PLATFORM_TYPE(BYTE);

DECLARE_PLATFORM_TYPE(UBYTE);

DECLARE_PLATFORM_TYPE(UCHAR);

DECLARE_PLATFORM_TYPE(ANSICHAR);

DECLARE_PLATFORM_TYPE(WIDECHAR);

DECLARE_PLATFORM_TYPE(CHAR16);

DECLARE_PLATFORM_TYPE(CHAR32);

DECLARE_PLATFORM_TYPE(TCHAR);



#endif