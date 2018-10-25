#pragma once

#include"class_defines.h"

extern "C"
{
	MusicProperty LoadFileMonaural16bits(std::string path);

	void createFile(std::string path, MusicProperty* prop);
}