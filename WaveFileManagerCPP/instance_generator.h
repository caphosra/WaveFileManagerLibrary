#pragma once

#include "class_defines.h"

extern "C"
{
	///
	/// Default is 44100Hz (SamplesPerSec)
	///
	void generateWAVEFORMATEX(WAVEFORMATEX* format, EDataType type);

	WAVEFORMATEX getWAVEFORMATEX_Default(EDataType type);

	void generateMusicProperty(MusicProperty* mpm, WAVEFORMATEX* waveFormat, EDataType type, Int8* data, UInt32 size);
}
