#pragma once
// #include "Foundation/Platform.h"
#include "Foundation/BuildType.hpp"

//window 平台
#include <crtdbg.h>
#define GOD_ASSERT_IMPL(EXPR)		_ASSERTE(EXPR)



#if defined(_DEBUG)
#define GOD_ASSERT(EXPR)		GOD_ASSERT_IMPL(EXPR)
#elif defined(_RELEASE)
#define GOD_ASSERT(EXPR)		((void)0)
#else
#define GOD_ASSERT(EXPR)		((void)0)
#endif