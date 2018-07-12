#pragma once

#include <string>
#include <cstdarg>

namespace StringUtils
{
	std::string GetCommandLineArg(int inIndex);

	std::string Sprintf(const char* inFormat, ...);

	void	Log(const char* inFormat);
	void	Log(const char* inFormat, ...);
}

#define LOG( ... ) StringUtils::Log( __VA_ARGS__ );