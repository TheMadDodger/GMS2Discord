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



// reference additional headers your program requires here


// Defines
#define GMExport extern "C" __declspec (dllexport)

// Discord RPC
#pragma comment(lib, "discord-rpc.lib")
#include "discord_rpc.h"