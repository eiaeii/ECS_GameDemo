#pragma once

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
typedef int socklen_t;
#endif
#include <cstdint>
#include <cassert>
#include <array>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "macro.h"

#include "game_math.h"
#include "crc_hash.h"
#include "ecs_fwd.h"
#include "ecs_type_traits.h"

#include "object.h"
