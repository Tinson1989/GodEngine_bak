#pragma once

#define GOD_UNKNOWN				"unknown"
#define GOD_WINDOWS				"windows"
#define GOD_MACOS				"macos"
#define GOD_IOS					"ios"
#define GOD_ANDROID				"android"

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
	#define GOD_PLATFORM	GOD_UNKNOWN
	#define GOD_WINDOWS
#elif  defined(__APPLE__)
	#define GOD_PLATFORM	GOD_MACOS
	#define GOD_MACOS
#else
	#define GOD_PLATFORM	GOD_UNKNOWN
	#define GOD_UNKNOWN
#endif