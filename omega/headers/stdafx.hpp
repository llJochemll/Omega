// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.hpp"

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

//Common headers
#include "intercept.hpp"

//Common namespaces
using namespace intercept;
using namespace intercept::types;