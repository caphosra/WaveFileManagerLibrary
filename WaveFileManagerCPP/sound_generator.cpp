#include "sound_generator.h"

#define _USE_MATH_DEFINES
#include<math.h>
#undef _USE_MATH_DEFINES

extern "C" void generateSoundMonaural16bits(Int8* begin, UInt32 size, double herth, int samplesPerSec, int volume)
{
	Int16 sound;

	for (int i = 0; i < (size / 2); i++)
	{
		sound = ((short)(sin(i / (double)samplesPerSec * 2 * M_PI * herth) * volume));
		memcpy(begin + (i * 2), &sound, sizeof(Int16));
	}
}