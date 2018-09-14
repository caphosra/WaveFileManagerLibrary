#pragma once

#include<vector>
#include<string>
#include<fstream>

typedef int Int32;
typedef short Int16;
typedef char Int8;
typedef unsigned int UInt32;
typedef unsigned short UInt16;

struct WAVEFORMATEX
{
public:
	Int16 wFormatTag;
	UInt16 nChannels;
	UInt32 nSamplesPerSec;
	UInt32 nAvgBytePerSec;
	UInt16 nBlockAlign;
	UInt16 wBitsPerSample;

	/// <summary>
	/// Monaural 16bits 44100Hz
	/// </summary>
	WAVEFORMATEX getMonaural16bitsDefault();

	/// <summary>
	/// Monaural 8bits 44100Hz
	/// </summary>
	WAVEFORMATEX getMonaural8bitsDefault();
};

#pragma region WAVEFORMATEX Implement

WAVEFORMATEX WAVEFORMATEX::getMonaural16bitsDefault()
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

WAVEFORMATEX WAVEFORMATEX::getMonaural8bitsDefault()
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

#pragma endregion

struct MusicDataMonaural16bit
{
public:
	Int32 m_DataSize;
	std::vector<Int16> m_Data;
};

struct MusicDataMonaural8bit
{
public:
	Int32 m_DataSize;
	std::vector<Int8> m_Data;
};

struct MusicProperty
{
public:
	Int32 m_FileSize;
	Int32 m_PCMWAVEFORMAT_Size;
	WAVEFORMATEX m_WaveFormatEx;
};

struct MusicPropertyMonaural16bit : public MusicProperty
{
public:
	MusicDataMonaural16bit m_MusicData;
};

struct MusicPropertyMonaural8bit : public MusicProperty
{
public:
	MusicDataMonaural8bit m_MusicData;
};

class WaveFileManager
{
public:
	MusicPropertyMonaural16bit LoadFileMonaural16bits(std::string path);
	
	void createFile(std::string path, MusicPropertyMonaural16bit* prop);
	void createFile(std::string path, MusicPropertyMonaural8bit* prop);

private:
	void writeMusicProperty(std::fstream* fs, MusicProperty* prop);
	void writeWAVEFORMATEX(std::fstream* fs, WAVEFORMATEX* format);

	void readMusicProperty(std::fstream* fs, MusicProperty* prop);
	void readWAVEFORMATEX(std::fstream* fs, WAVEFORMATEX* format);
};

//
// Word Array
//
Int8 RIFF[]{ 0x52, 0x49, 0x46, 0x46 };
Int8 WAVE[]{ 0x57, 0x41, 0x56, 0x45 };
Int8 fmt[]{ 0x66, 0x6D, 0x74, 0x20 };
Int8 data_CONST[]{ 0x64, 0x61, 0x74, 0x61 };

#pragma region ConvertFromArrayToNumber

Int32 convertToInt32(Int8* bytes)
{
	Int32 i;
	memcpy(&i, bytes, sizeof(Int32));
	return i;

}

Int16 convertToInt16(Int8* bytes)
{
	Int16 i;
	memcpy(&i, bytes, sizeof(Int16));
	return i;
}

#pragma endregion

#if WFM_CAN_USE_TEMPLATE
/// <summary>
/// The arrays are same ?
/// </summary>
template<typename T>
bool sequenceEqual(T* a, T* b, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (a[i] != b[i]) return false;
	}
	return true;
}
#else
/// <summary>
/// The arrays are same ?
/// </summary>
bool sequenceEqual(Int8* a, Int8* b, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (a[i] != b[i]) return false;
	}
	return true;
}
#endif
