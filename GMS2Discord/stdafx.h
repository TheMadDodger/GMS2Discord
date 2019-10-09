// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>



// reference additional headers your program requires here


// Defines
#define GMExport extern "C" __declspec (dllexport)

#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

// Discord RPC
#pragma comment(lib, "discord_game_sdk.dll.lib")
#include "discord.h"