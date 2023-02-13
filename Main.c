#include "Core.h"
#include "Platform.h"
#include "Logging.h"

int main()
{
	if (!Logging_Init())
	{
		printf("Failed to initialise logging");
		exit(1);
	}

	Platform_Init();
}