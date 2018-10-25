#pragma once

#include"class_defines.h"

#ifndef WAVEFILE_API
	#define WAVEFILE_API 
#endif

extern "C"
{
	MusicProperty WAVEFILE_API LoadFileMonaural16bits(std::string path);

	void WAVEFILE_API createFile(std::string path, MusicProperty* prop);
}