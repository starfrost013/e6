#include "Core.h"
#include "Init.h"
#include "Logging.h"
#include "Platform.h"


int main()
{
	if (!Logging_Init())
	{
		printf("Failed to initialise logging");
		exit(1);
	}

	Platform_Init();
	Engine_Init(); 
}