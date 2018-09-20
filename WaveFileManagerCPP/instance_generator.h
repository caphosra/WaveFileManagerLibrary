#pragma once

#include "class_defines.h"

///
/// Default is 44100Hz (SamplesPerSec)
///
void getWAVEFORMATEX_Default(WAVEFORMATEX* format, EDataType type)
{
	switch(type)
	{
		case MONAURAL_16BITS:
			{
				format->wFormatTag = 1;
				format->nChannels = 1;
				format->nSamplesPerSec = 44100;
				format->nAvgBytePerSec = 88200;
				format->nBlockAlign = 2;
				format->wBitsPerSample = 16;
			}
			break;
		case MONAURAL_8BITS:
			{
				format->wFormatTag = 1;
				format->nChannels = 1;
				format->nSamplesPerSec = 44100;
				format->nAvgBytePerSec = 44100;
				format->nBlockAlign = 1;
				format->wBitsPerSample = 8;
			}
			break;
	}
	
}

WAVEFORMATEX getWAVEFORMATEX_Default(EDataType type)
{
	WAVEFORMATEX format;
	getWAVEFORMATEX_Default(&format, type);
	return format;
	
}

void generateMusicProperty(MusicProperty* mpm, EDataType dataType, Int8* data, UInt32 size)
{
	mpm->m_FileSize = 36 + size;
	mpm->m_PCMWAVEFORMAT_Size = 16;

	WAVEFORMATEX waveformat;
	mpm->m_WaveFormatEx = getWAVEFORMATEX_Default(dataType);

	mpm->m_DataSize = size;
	mpm->m_DataType = dataType;
	mpm->m_Data = data;
}
