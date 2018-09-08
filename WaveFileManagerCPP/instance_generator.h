#pragma once

#include "class_defines.h"

MusicPropertyMonaural16bit GenerateMonaural16bits(Int16* data, UInt32 length)
{
	MusicPropertyMonaural16bit w;

	w.m_FileSize = 36 + (sizeof(Int16) * length);
	w.m_PCMWAVEFORMAT_Size = 16;

	WAVEFORMATEX waveformat;
	w.m_WaveFormatEx = waveformat.GetMonaural16bitsDefault();

	MusicDataMonaural16bit data16bit;
	data16bit.m_DataSize = (sizeof(Int16) * length);

	std::vector<Int16> v;
	v.assign(data, data + length);
	data16bit.m_Data = v;
	w.m_MusicData = data16bit;

	return w;
}

MusicPropertyMonaural8bit GenerateMonaural8bits(Int8* data, UInt32 length)
{
	MusicPropertyMonaural8bit w;

	w.m_FileSize = 36 + (sizeof(Int8) * length);
	w.m_PCMWAVEFORMAT_Size = 16;

	WAVEFORMATEX waveformat;
	w.m_WaveFormatEx = waveformat.GetMonaural8bitsDefault();

	MusicDataMonaural8bit data8bit;
	data8bit.m_DataSize = (sizeof(Int8) * length);
	
	std::vector<Int8> v;
	v.assign(data, data + length);
	data8bit.m_Data = v;
	w.m_MusicData = data8bit;

	return w;
}