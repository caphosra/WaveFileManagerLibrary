#pragma once

#include "class_defines.h"

#define _USE_MATH_DEFINES
#include<math.h>

// Return sounds data
void generateSoundMonaural16bits(Int8* begin, UInt32 size, double herth, int samplesPerSec = 44100, int volume = 30000)
{
	Int16 sound;

	for (int i = 0; i < (size / 2); i++)
	{
		sound = ((short)(sin(i / (double)samplesPerSec * 2 * M_PI * herth) * volume));
		memcpy(begin + (i * 2), &sound, sizeof(Int16));
	}
}
