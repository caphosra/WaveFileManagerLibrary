#pragma once

#include"class_defines.h"

/// <summary>
/// Load wave file that is made by this program.
/// </summary>
MusicPropertyMonaural16bit WaveFileManager::LoadFileMonaural16bits(std::string path)
{
	MusicPropertyMonaural16bit property;

	std::fstream fs(path, std::ios::in | std::ios::binary);

	Int8 byte_16[2];
	Int8 byte_32[4];

	#pragma region Get RIFF(It will be threw away)

	fs.read(byte_32, 4);

	if (!sequenceEqual(byte_32, RIFF, 4))
	{
		throw "It's not RIFF format file.";
	}

	#pragma endregion

	#pragma region Get FileSize
	fs.read(byte_32, 4);

	property.m_FileSize = convertToInt32(byte_32);

	#pragma endregion

	#pragma region Get WAVE(It will be threw away)

	// If the file loading is wave file, 
	// this function will return "WAVE".
	fs.read(byte_32, 4);

	if (!sequenceEqual(byte_32, WAVE, 4))
	{
		throw "It's not WAVE file.";
	}

	#pragma endregion

	#pragma region  Get fmt(It will be threw away)

	fs.read(byte_32, 4);

	if (!sequenceEqual(byte_32, fmt, 4))
	{
		throw "It's not WAVE file.";
	}

	#pragma endregion

	#pragma region  Get the size of PCMWAVEFORMAT

	fs.read(byte_32, 4);

	if (convertToInt32(byte_32) != 16)
	{
		throw "It will have unnecessary chank.";
	}

	#pragma endregion

	WAVEFORMATEX format;

	readWAVEFORMATEX(&fs, &format);

	#pragma region Get data(It will be threw away)

	fs.read(byte_32, 4);

	if (!sequenceEqual(byte_32, data_CONST, 4))
	{
		throw "It's not WAVE file.";
	}

	#pragma endregion

	MusicDataMonaural16bit musicData;

	#pragma region Get DataSize

	fs.read(byte_32, 4);

	musicData.m_DataSize = convertToInt32(byte_32);

	#pragma endregion

	#pragma region Get Data

	std::vector<Int16> list;

	for (; ; )
	{
		fs.read(byte_16, 2);
		if (fs.eof())
			break;
		list.push_back(convertToInt16(byte_16));
	}

	musicData.m_Data = list;

	#pragma endregion

	// Close the file stream.
	fs.close();

	property.m_WaveFormatEx = format;
	property.m_MusicData = musicData;

	return property;
}

void WaveFileManager::readWAVEFORMATEX(std::fstream* fs, WAVEFORMATEX* format)
{
	Int8 i[4];

	fs->read(i, 2);
	format->wFormatTag = convertToInt16(i);

	fs->read(i, 2);
	format->nChannels = convertToInt16(i);

	fs->read(i, 4);
	format->nSamplesPerSec = convertToInt32(i);

	fs->read(i, 4);
	format->nAvgBytePerSec = convertToInt32(i);

	fs->read(i, 2);
	format->nBlockAlign = convertToInt16(i);

	fs->read(i, 2);
	format->wBitsPerSample = convertToInt16(i);
}
