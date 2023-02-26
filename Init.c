#include <SDL.h>
#include <SDL_version.h>

#include "Init.h"
#include "Logging.h"

bool Engine_Init()
{
	Logging_Log("Initialising SDL");

	SDL_version version;

	memset(&version, 0x00, sizeof version);

	SDL_GetVersion(&version);

	if (!SDL_Init(SDL_INIT_EVERYTHING))
;	{
		Logging_LogError("Failed to initialise SDL", 10, LoggingSeverityFatal);
	}

}

bool Engine_Shutdown()
{

}