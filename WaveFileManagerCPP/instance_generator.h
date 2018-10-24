#pragma once

#include "class_defines.h"

#ifndef WAVEFILE_API
	#define WAVEFILE_API 
#endif

extern "C"
{
	///
	/// Default is 44100Hz (SamplesPerSec)
	///
	void WAVEFILE_API generateWAVEFORMATEX(WAVEFORMATEX* format, EDataType type);

	WAVEFORMATEX WAVEFILE_API getWAVEFORMATEX_Default(EDataType type);

	void  WAVEFILE_API generateMusicProperty(MusicProperty* mpm, WAVEFORMATEX* waveFormat, EDataType type, Int8* data, UInt32 size);
}
