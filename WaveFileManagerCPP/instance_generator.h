#pragma once

#include "class_defines.h"

///
/// Default is 44100Hz (SamplesPerSec)
///
void getWAVEFORMATEX_Default(WAVEFORMATEX* format, EFileType type)
{
	switch(type)
	{
		case Monaural8bits:
			{
				format->wFormatTag = 1;
				format->nChannels = 1;
				format->nSamplesPerSec = 44100;
				format->nAvgBytePerSec = 88200;
				format->nBlockAlign = 2;
				format->wBitsPerSample = 16;
			}
			break;
		case Monaural16bits:
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

WAVEFORMATEX getWAVEFORMATEX_Default(EFileType type)
{
	WAVEFORMATEX format;
	getWAVEFORMATEX_Default(&format, type);
	return format;
	
}

void generateMonaural16bits(MusicPropertyMonaural16bit* mpm, Int16* data, UInt32 length)
{
	mpm->m_FileSize = 36 + (sizeof(Int16) * length);
	mpm->m_PCMWAVEFORMAT_Size = 16;

	WAVEFORMATEX waveformat;
	mpm->m_WaveFormatEx = getWAVEFORMATEX_Default(Monaural16bits);

	MusicDataMonaural16bit data16bit;
	data16bit.m_DataSize = (sizeof(Int16) * length);

	std::vector<Int16> v;
	v.assign(data, data + length);
	data16bit.m_Data = v;
	mpm->m_MusicData = data16bit;
}

MusicPropertyMonaural16bit generateMonaural16bits(Int16* data, UInt32 length)
{
	MusicPropertyMonaural16bit w;
	generateMonaural16bits(&w, data, length);
	return w;
}

MusicPropertyMonaural8bit generateMonaural8bits(Int8* data, UInt32 length)
{
	MusicPropertyMonaural8bit w;

	w.m_FileSize = 36 + (sizeof(Int8) * length);
	w.m_PCMWAVEFORMAT_Size = 16;

	WAVEFORMATEX waveformat;
	w.m_WaveFormatEx = getWAVEFORMATEX_Default(Monaural8bits);

	MusicDataMonaural8bit data8bit;
	data8bit.m_DataSize = (sizeof(Int8) * length);
	
	std::vector<Int8> v;
	v.assign(data, data + length);
	data8bit.m_Data = v;
	w.m_MusicData = data8bit;

	return w;
}