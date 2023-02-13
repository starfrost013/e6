#include "Core.h"
#include "Logging.h"
#include "Platform.h"

#ifdef E6_BUILD_WINDOWS

bool Platform_Init()
{
	Logging_LogColor("Init %s", ConsoleColorBlack, ConsoleColorGray, E6_BUILD_STRING);

	// initialise winsock 
	WSADATA wsaData;

	memset(&wsaData, 0x00, sizeof(wsaData));

	e6_int32 wsaInitResult;

	wsaInitResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (!SUCCEEDED(wsaInitResult))
	{
		Logging_LogError("Windows Sockets initialisation failed!", 0, LoggingSeverityFatal);
		return false;
	}

	Logging_Log("Winsock2 Initialised");

	return true;
}

void Platform_Error(char* err)
{
	// temporary until i write an actual log
	printf("(temp) Fatal error %s", err);
	exit(1);
}

bool Platform_Shutdown()
{
	// for now
	return true;
}

#endif
