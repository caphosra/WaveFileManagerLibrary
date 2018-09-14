#pragma once

#include "class_defines.h"

WAVEFORMATEX getWAVEFORMATEX_Default(EFileType type)
{
	switch(type)
	{
		case Monaural8bits:
			{
				WAVEFORMATEX format;
				format.wFormatTag = 1;
				format.nChannels = 1;
				format.nSamplesPerSec = 44100;
				format.nAvgBytePerSec = 88200;
				format.nBlockAlign = 2;
				format.wBitsPerSample = 16;
				return format;
			}
			break;
		case Monaural16bits:
			{
				WAVEFORMATEX format;
				format.wFormatTag = 1;
				format.nChannels = 1;
				format.nSamplesPerSec = 44100;
				format.nAvgBytePerSec = 44100;
				format.nBlockAlign = 1;
				format.wBitsPerSample = 8;
				return format;
			}
			break;
	}
	
}

MusicPropertyMonaural16bit generateMonaural16bits(Int16* data, UInt32 length)
{
	MusicPropertyMonaural16bit w;

	w.m_FileSize = 36 + (sizeof(Int16) * length);
	w.m_PCMWAVEFORMAT_Size = 16;

	WAVEFORMATEX waveformat;
	w.m_WaveFormatEx = waveformat.getMonaural16bitsDefault();

	MusicDataMonaural16bit data16bit;
	data16bit.m_DataSize = (sizeof(Int16) * length);

	std::vector<Int16> v;
	v.assign(data, data + length);
	data16bit.m_Data = v;
	w.m_MusicData = data16bit;

	return w;
}

MusicPropertyMonaural8bit generateMonaural8bits(Int8* data, UInt32 length)
{
	MusicPropertyMonaural8bit w;

	w.m_FileSize = 36 + (sizeof(Int8) * length);
	w.m_PCMWAVEFORMAT_Size = 16;

	WAVEFORMATEX waveformat;
	w.m_WaveFormatEx = waveformat.getMonaural8bitsDefault();

	MusicDataMonaural8bit data8bit;
	data8bit.m_DataSize = (sizeof(Int8) * length);
	
	std::vector<Int8> v;
	v.assign(data, data + length);
	data8bit.m_Data = v;
	w.m_MusicData = data8bit;

	return w;
}