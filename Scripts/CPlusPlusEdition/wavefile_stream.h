#pragma once

#include"class_defines.h"

extern "C"
{
	MusicProperty loadFileMonaural16bits(const char* path);

	void createFile(const char* path, MusicProperty* prop);
}