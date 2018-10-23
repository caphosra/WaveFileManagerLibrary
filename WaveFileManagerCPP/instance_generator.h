#pragma once

#include "class_defines.h"

///
/// Default is 44100Hz (SamplesPerSec)
///
void getWAVEFORMATEX_Default(WAVEFORMATEX* format, EDataType type);

WAVEFORMATEX getWAVEFORMATEX_Default(EDataType type);

void generateMusicProperty(MusicProperty* mpm, EDataType dataType, Int8* data, UInt32 size);
