#ifndef __SCAN_PLATFORM_TYPES_H__
#define __SCAN_PLATFORM_TYPES_H__

#include <cstdint>



namespace SB::Platform::Types
{

	// signed integer types

	using int8		= std::int32_t;

	using int16		= std::int16_t;

	using int32		= std::int32_t;

	using int64		= std::int64_t;

	
	// unsigned integer types

	using uint8		= std::uint8_t;

	using uint16	= std::uint16_t;

	using uint32	= std::uint32_t;

	using uint64	= std::uint64_t;


	// other types


	using SIZE_T	= unsigned long long;


	using BYTE		= char;

	using UBYTE		= unsigned char;


	using UCHAR		= unsigned char;

	using ANSICHAR	= char;

	using WIDECHAR	= wchar_t;

	using CHAR16	= char16_t;

	using CHAR32	= char32_t;
	

	using TCHAR		= ANSICHAR;



}



#endif