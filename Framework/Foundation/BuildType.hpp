#pragma once

// Debug。不对代码进行优化，保留所有符号数据库以便于调试。
// Release。对代码进行优化。
// RelWithDebInfo。与Release相同，但是会保留符号数据库。
// MinSizeRel。与Release相同，但是会要求产生最小的二进制文件。
#define BUILD_TYPE_UNKNOWN			    "unknown"
#define BUILD_TYPE_DEBUG			    "Debug"
#define BUILD_TYPE_RELEASE			    "Release"
#define BUILD_TYPE_RELEASEWITHDEBINFO	"RelWithDebInfo"
#define BUILD_TYPE_MINSIZEREL			"MinSizeRel"

#if defined(_DEBUG)
#define BUILD_TYPE	BUILD_TYPE_DEBUG
#elif defined(_RELEASE)
#define BUILD_TYPE	BUILD_TYPE_RELEASE
#elif defined(_RELEASEWITHDEBINFO)
#define BUILD_TYPE	BUILD_TYPE_RELEASEWITHDEBINFO
#elif defined(_MINSIZEREL)
#define BUILD_TYPE	BUILD_TYPE_MINSIZEREL
#else
#define BUILD_TYPE	BUILD_TYPE_UNKNOWN
#endif
