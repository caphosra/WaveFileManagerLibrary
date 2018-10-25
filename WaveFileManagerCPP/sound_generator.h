#pragma once

#include"class_defines.h"

// Return sounds data
extern "C" void generateSoundMonaural16bits(Int8* begin, UInt32 size, double herth, int samplesPerSec = 44100, int volume = 30000);
