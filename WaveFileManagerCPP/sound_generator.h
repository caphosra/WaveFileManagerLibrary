#pragma once

#include"class_defines.h"

#ifndef WAVEFILE_API
	#define WAVEFILE_API 
#endif

// Return sounds data
extern "C" void WAVEFILE_API generateSoundMonaural16bits(Int8* begin, UInt32 size, double herth, int samplesPerSec = 44100, int volume = 30000);
