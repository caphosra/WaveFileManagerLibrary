#pragma once

#include "DefineClass.h"

#define _USE_MATH_DEFINES
#include<math.h>

// Return  sounds data (length : samplesPerSec * 2)
void GenerateSoundMonaural16bits(Int16* sound, double herth, int samplesPerSec = 44100)
{
	for (int i = 0; i < samplesPerSec * 2; i++)
	{
		sound[i] = ((short)(sin(i / (double)samplesPerSec * 2 * M_PI * herth) * 30000));
	}
}
