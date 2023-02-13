#include "Core.h"
#include "Logging.h"
#include "Platform.h"

// a few global variables
// at some point these will be loaded from gvar
FILE *logging_stream;

char* E6_LOGGING_PREFIX = "E6Log-";
char* E6_LOGGING_SUFFIX = ".log";

// 'internal' func prototypes
char* Logging_GetCurrentTime();

bool Logging_Init()
{
	char log_file_name[64];

	memset(&log_file_name, 0x00, sizeof(char) * 64);

	strcat_s(log_file_name, sizeof log_file_name, E6_LOGGING_PREFIX);
	strcat_s(log_file_name, sizeof log_file_name, "current");
	strcat_s(log_file_name, sizeof log_file_name, E6_LOGGING_SUFFIX);

	e6_int32 error = fopen_s(&logging_stream, log_file_name, "w+");

	if (error != 0)
	{
		printf("Failed to open log stream (%d)\n", error);
		return false;
	}

	return true;
}

char* Logging_GetCurrentTime()
{
	// build the logging file name 
	time_t cur_time;
	struct tm decomposed_cur_time;
	char file_name[48];

	memset(&file_name, 0x00, sizeof(char) * 48);

	cur_time = time(NULL);
	localtime_s(&decomposed_cur_time, &cur_time);

	strftime(file_name, 32, "%Y-%m-%d %H:%M:%S", &decomposed_cur_time);

	return file_name;
}

bool Logging_Log(char* text, ...)
{
	va_list args;

	va_start(args, text);
	
	bool result = Logging_LogColor(text, ConsoleColorGray, ConsoleColorBlack, args);
	va_end(args);

	return result;
}

// write to the log file and the console
bool Logging_LogColor(char* text, enum ConsoleColor foreground_color, enum ConsoleColor background_color, ...)
{
	char final_log_string[512];

	memset(&final_log_string, 0x00, sizeof(char) * 512);

	char* current_time = Logging_GetCurrentTime();

	// build date prefix
	strcat_s(final_log_string, sizeof final_log_string, "[");
	strcat_s(final_log_string, sizeof final_log_string, current_time);
	strcat_s(final_log_string, sizeof final_log_string, "]: ");

	size_t final_length = strlen(final_log_string) + strlen(text) + 1; // 1 for new line

	// truncate if too long
	if (final_length > sizeof final_log_string) text[sizeof final_log_string - 1] = '\0';
	
	strcat_s(final_log_string, sizeof final_log_string, text);
	strcat_s(final_log_string, sizeof final_log_string, "\n");


	// set the console color...
	// use VTS
	printf("\033[%dm", foreground_color);
	printf("\033[%dm", background_color + 10); // the values for background are 10 higher than foreground

	// output to the console
	va_list args;

	// point at the last argument
	va_start(args, background_color);

	vfprintf(stdout, final_log_string, args);

	// output to log file
	vfprintf(logging_stream, final_log_string, args);

	va_end(args);

	return true;
}

void Logging_LogError(char* text, int code, enum LoggingSeverity severity)
{
	switch (severity)
	{
		case LoggingSeverityWarning:
			Logging_LogColor("Warning [%d]: %s\n", ConsoleColorYellow, ConsoleColorGray, code, text);
			break;
		case LoggingSeverityError:
			Logging_LogColor("Error [%d]: %s\n", ConsoleColorRed, ConsoleColorGray, code, text);
			break;
		case LoggingSeverityFatal:
			Logging_LogColor("Fatal Error [%d]: %s.\n", ConsoleColorRed, ConsoleColorGray, code, text);
			Platform_Shutdown();
			break;
	}
}

bool Logging_Shutdown()
{
	if (fclose(logging_stream) != 0)
	{
		printf("Failed to close logging stream\n");
		return false;
	}

	return true;
}