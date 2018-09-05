#pragma once

#include"class_defines.h"

#include<fstream>

//
// Load to following array.
//
Int8 RIFF[]{ 0x52, 0x49, 0x46, 0x46 };
Int8 WAVE[]{ 0x57, 0x41, 0x56, 0x45 };
Int8 fmt[]{ 0x66, 0x6D, 0x74, 0x20 };
Int8 data_CONST[]{ 0x64, 0x61, 0x74, 0x61 };

/// <summary>
/// Load wave file that is made by this program.
/// </summary>
MusicPropertyMonaural16bit WaveFileManager::LoadFileMonaural16bits(std::string path)
{
	MusicPropertyMonaural16bit property;

	std::ifstream ifs(path, std::ios::in | std::ios::binary);

	Int8 byte_16[2];
	Int8 byte_32[4];

	#pragma region Get RIFF(It will be threw away)

	ifs.read(byte_32, 4);

	if (!SequenceEqual(byte_32, RIFF, 4))
	{
		throw "It's not RIFF format file.";
	}

	#pragma endregion

	#pragma region Get FileSize
	ifs.read(byte_32, 4);

	property.m_FileSize = ConvertToInt32(byte_32);

	#pragma endregion

	#pragma region Get WAVE(It will be threw away)

	// If the file loading is wave file, 
	// this function will return "WAVE".
	ifs.read(byte_32, 4);

	if (!SequenceEqual(byte_32, WAVE, 4))
	{
		throw "It's not WAVE file.";
	}

	#pragma endregion

	#pragma region  Get fmt(It will be threw away)

	ifs.read(byte_32, 4);

	if (!SequenceEqual(byte_32, fmt, 4))
	{
		throw "It's not WAVE file.";
	}

	#pragma endregion

	#pragma region  Get the size of PCMWAVEFORMAT

	ifs.read(byte_32, 4);

	if (ConvertToInt32(byte_32) != 16)
	{
		throw "It will have unnecessary chank.";
	}

	#pragma endregion

	WAVEFORMATEX format;
	format = format.GetMonaural16bitsDefault();

	#pragma region Get FormatTag

	ifs.read(byte_16, 2);

	if (format.wFormatTag != ConvertToInt16(byte_16))
	{
		throw "It's WAVE file but does not correspond to this. arg=wFormatTag";
	}

	#pragma endregion

	#pragma region Get Channels

	ifs.read(byte_16, 2);

	if (format.nChannels != ConvertToInt16(byte_16))
	{
		throw "It's WAVE file but does not correspond to this. arg=nChannels";
	}

	#pragma endregion

	#pragma region Get SamplesPerSec

	ifs.read(byte_32, 4);

	if (format.nSamplesPerSec != ConvertToInt32(byte_32))
	{
		throw "It's WAVE file but does not correspond to this. arg=nSamplesPerSec";
	}

	#pragma endregion

	#pragma region  Get AvgBytePerSec

	ifs.read(byte_32, 4);

	if (format.nAvgBytePerSec != ConvertToInt32(byte_32))
	{
		throw "It's WAVE file but does not correspond to this. arg=nAvgBytePerSec";
	}

	#pragma endregion

	#pragma region Get BlockAlign

	ifs.read(byte_16, 2);

	if (format.nBlockAlign != ConvertToInt16(byte_16))
	{
		throw "It's WAVE file but does not correspond to this. arg=nBlockAlign";
	}

	#pragma endregion

	#pragma region Get BitsPerSample

	ifs.read(byte_16, 2);

	if (format.wBitsPerSample != ConvertToInt16(byte_16))
	{
		throw "It's WAVE file but does not correspond to this. arg=wBitsPerSample";
	}

	#pragma endregion

	#pragma region Get data(It will be threw away)

	ifs.read(byte_32, 4);

	if (!SequenceEqual(byte_32, data_CONST, 4))
	{
		throw "It's not WAVE file.";
	}

	#pragma endregion

	MusicDataMonaural16bit musicData;

	#pragma region Get DataSize

	ifs.read(byte_32, 4);

	musicData.m_DataSize = ConvertToInt32(byte_32);

	#pragma endregion

	#pragma region Get Data

	std::vector<Int16> list;

	for (; ; )
	{
		ifs.read(byte_16, 2);
		if (ifs.eof())
			break;
		list.push_back(ConvertToInt16(byte_16));
	}

	musicData.m_Data = list;

	#pragma endregion

	// Close the file stream.
	ifs.close();

	property.m_WaveFormatEx = format;
	property.m_MusicData = musicData;

	return property;
}

/// <summary>
/// Create simple wave file.
/// </summary>
void WaveFileManager::CreateFile(std::string path, MusicPropertyMonaural16bit prop)
{
	std::fstream fs(path, std::ios::out | std::ios::binary);

	WriteMusicProperty(&fs, prop);

	WAVEFORMATEX format = prop.m_WaveFormatEx;

	WriteWAVEFORMATEX(&fs, format);

	fs.write(data_CONST, 4);

	MusicDataMonaural16bit musicData = prop.m_MusicData;
	{
		//It means nothing.
		Int8 int8array[4];

		ConvertToLittleEndian(int8array, musicData.m_DataSize);
		fs.write(int8array, sizeof(Int32));

#pragma warning(push)
#pragma warning(disable:4018)
		for (int i = 0; i < musicData.m_Data.size(); i++)
		{
			ConvertToLittleEndian(int8array, musicData.m_Data[i]);
			fs.write(int8array, sizeof(Int16));
		}
#pragma warning(pop)
	}

	// Close the file stream.
	fs.close();
}

/// <summary>
/// Create simple wave file.
/// </summary>
void WaveFileManager::CreateFile(std::string path, MusicPropertyMonaural8bit prop)
{
	std::fstream fs(path, std::ios::out | std::ios::binary);

	WriteMusicProperty(&fs, prop);

	WAVEFORMATEX format = prop.m_WaveFormatEx;

	WriteWAVEFORMATEX(&fs, format);

	fs.write(data_CONST, 4);

	MusicDataMonaural8bit musicData = prop.m_MusicData;
	{
		// It means nothing.
		Int8 int8array[4];

		ConvertToLittleEndian(int8array, musicData.m_DataSize);
		fs.write(int8array, 4);

#pragma warning(push)
#pragma warning(disable:4018)
		for (int i = 0; i < musicData.m_Data.size(); i++)
		{
			ConvertToLittleEndian(int8array, musicData.m_Data[i]);
			fs.write(int8array, sizeof(Int8));
		}
#pragma warning(pop)
	}

	// Close the file stream.
	fs.close();
}

//
// private member
//
void WaveFileManager::WriteMusicProperty(std::fstream* fs, MusicProperty prop)
{
	Int8 i[4];

	fs->write(RIFF, 4);

	ConvertToLittleEndian(i, prop.m_FileSize);
	fs->write(i, 4);

	fs->write(WAVE, 4);

	fs->write(fmt, 4);

	ConvertToLittleEndian(i, prop.m_PCMWAVEFORMAT_Size);
	fs->write(i, 4);
}

void WaveFileManager::WriteWAVEFORMATEX(std::fstream* fs, WAVEFORMATEX format)
{
	Int8 i[4];

	ConvertToLittleEndian(i, format.wFormatTag);
	fs->write(i, 2);

	ConvertToLittleEndian(i, format.nChannels);
	fs->write(i, 2);

	ConvertToLittleEndian(i, format.nSamplesPerSec);
	fs->write(i, 4);

	ConvertToLittleEndian(i, format.nAvgBytePerSec);
	fs->write(i, 4);

	ConvertToLittleEndian(i, format.nBlockAlign);
	fs->write(i, 2);

	ConvertToLittleEndian(i, format.wBitsPerSample);
	fs->write(i, 2);
}
