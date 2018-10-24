#include "instance_generator.h"

extern "C"
{
	///
	/// Default is 44100Hz (SamplesPerSec)
	///
	void generateWAVEFORMATEX(WAVEFORMATEX* format, EDataType type)
	{
		switch (type)
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
		generateWAVEFORMATEX(&format, type);
		return format;

	}

	void generateMusicProperty(MusicProperty* mpm, WAVEFORMATEX* waveFormat, EDataType type, Int8* data, UInt32 size)
	{
		mpm->m_FileSize = 36 + size;
		mpm->m_PCMWAVEFORMAT_Size = 16;

		mpm->m_WaveFormatEx = *waveFormat;

		mpm->m_DataSize = size;
		mpm->m_DataType = type;
		mpm->m_Data = data;
	}
}
