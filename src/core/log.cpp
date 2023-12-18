#include "log.h"

#include <stdio.h>
#include <stdarg.h> 
#include <stdio.h> 

#if WIN
#include <Windows.h>
#include <debugapi.h>
#endif

void log_info(const char* str, ...)
{
	char msg[5000];
	va_list ap;
	va_start(ap, str);
	vsnprintf(msg, sizeof(char) * 5000, str, ap);
	va_end(ap);
	
	
	// only useful when working with visual studio
#if WIN && _MSC_VER
	OutputDebugStringA(msg);
#endif
	printf("%s\n", msg);
}


void log_error(const char* str, ...)
{
	char msg[5000];
	va_list ap;
	va_start(ap, str);
	vsnprintf(msg, sizeof(char) * 5000, str, ap);
	va_end(ap);

#if !DEBUG && WIN
	MessageBox(NULL, str, msg, MB_OKCANCEL);
#elif WIN && _MSC_VER
	OutputDebugString(msg);
#endif
	printf("ERROR: %s\n", msg);
}