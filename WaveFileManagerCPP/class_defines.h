#pragma once

#include<vector>
#include<string>

typedef int Int32;
typedef short Int16;
typedef char Int8;
typedef unsigned int UInt32;
typedef unsigned short UInt16;

class WAVEFORMATEX
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
	WAVEFORMATEX GetMonaural16bitsDefault();

	/// <summary>
	/// Monaural 8bits 44100Hz
	/// </summary>
	WAVEFORMATEX GetMonaural8bitsDefault();
};

#pragma region WAVEFORMATEX Implement

WAVEFORMATEX WAVEFORMATEX::GetMonaural16bitsDefault()
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

WAVEFORMATEX WAVEFORMATEX::GetMonaural8bitsDefault()
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

class MusicProperty
{
public:
	Int32 m_FileSize;
	Int32 m_PCMWAVEFORMAT_Size;
	WAVEFORMATEX m_WaveFormatEx;
};

class MusicPropertyMonaural16bit : public MusicProperty
{
public:
	MusicDataMonaural16bit m_MusicData;
};

class MusicPropertyMonaural8bit : public MusicProperty
{
public:
	MusicDataMonaural8bit m_MusicData;
};

class WaveFileManager
{
public:
	MusicPropertyMonaural16bit LoadFileMonaural16bits(std::string path);
	
	void CreateFile(std::string path, MusicPropertyMonaural16bit prop);
	void CreateFile(std::string path, MusicPropertyMonaural8bit prop);

private:
	void WriteMusicProperty(std::fstream* fs, MusicProperty prop);
	void WriteWAVEFORMATEX(std::fstream* fs, WAVEFORMATEX format);

	void ReadMusicProperty(std::fstream* fs, MusicProperty* prop);
	void ReadWAVEFORMATEX(std::fstream* fs, WAVEFORMATEX* format);
};

//
// Word Array
//
Int8 RIFF[]{ 0x52, 0x49, 0x46, 0x46 };
Int8 WAVE[]{ 0x57, 0x41, 0x56, 0x45 };
Int8 fmt[]{ 0x66, 0x6D, 0x74, 0x20 };
Int8 data_CONST[]{ 0x64, 0x61, 0x74, 0x61 };

#pragma region ConvertFromNumberToArray

void ConvertToLittleEndian(Int8* c, Int32 int32)
{
	memcpy(c, &int32, sizeof(int32));
}

void ConvertToLittleEndian(Int8* c, Int16 int16)
{
	memcpy(c, &int16, sizeof(int16));
}

void ConvertToLittleEndian(Int8* c, UInt32 int32)
{
	memcpy(c, &int32, sizeof(int32));
}

void ConvertToLittleEndian(Int8* c, UInt16 int16)
{
	memcpy(c, &int16, sizeof(int16));
}

#pragma endregion

#pragma region ConvertFromArrayToNumber

Int32 ConvertToInt32(Int8* bytes)
{
	Int32 i;
	memcpy(&i, bytes, sizeof(Int8) * 4);
	return i;

}

Int16 ConvertToInt16(Int8* bytes)
{
	Int16 i;
	memcpy(&i, bytes, sizeof(Int16));
	return i;
}

#pragma endregion

#if CAN_USE_TEMPLATE_IN_WAVEFILEMANAGER
/// <summary>
/// The arrays are same ?
/// </summary>
template<typename T>
bool SequenceEqual(T* a, T* b, int count)
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
bool SequenceEqual(Int8* a, Int8* b, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (a[i] != b[i]) return false;
	}
	return true;
}
#endif
