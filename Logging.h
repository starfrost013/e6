#pragma once
#include "Core.h"
// Core logging stuff

// Some logging severities
enum LoggingSeverity
{
	LoggingSeverityWarning = 0,
	LoggingSeverityError = 1,
	LoggingSeverityFatal = 2,
};

// Some console colors.
enum ConsoleColor
{
	// add 10 for background
	ConsoleColorBlack = 30,
	ConsoleColorRed = 31,
	ConsoleColorGreen = 32,
	ConsoleColorYellow = 33,
	ConsoleColorBlue = 34,
	ConsoleColorMagenta = 35,
	ConsoleColorCyan = 36,
	ConsoleColorWhite = 37,
	ConsoleColorGray = 90,
	ConsoleColorLightRed = 91,
	ConsoleColorLightGreen = 92,
	ConsoleColorLightYellow = 93,
	ConsoleColorLightBlue = 94,
	ConsoleColorLightMagenta = 95,
	ConsoleColorLightCyan = 96,
	ConsoleColorLightWhite = 97,
};


bool Logging_Init();
bool Logging_Log(char* text, ...);
bool Logging_LogColor(char* text, enum ConsoleColor foreground_color, enum ConsoleColor background_color, ...);
void Logging_LogError(char* text, int code, enum LoggingSeverity severity);
bool Logging_Shutdown();