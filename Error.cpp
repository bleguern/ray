#include "Error.h"



void Error(const char* str_error)
{
	MessageBox(NULL, str_error, "Ray 3D Engine : Error", MB_ICONERROR | MB_OK);
}


bool Warning(const char* str_warning)
{
	FILE *fd;

	if((fd = fopen(WARNING_FILE, "a")) == NULL)
		return false;

	fprintf(fd, "%s\n", str_warning);

	fclose(fd);
	return true;
}