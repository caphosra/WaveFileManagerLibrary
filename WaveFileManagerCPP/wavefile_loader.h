#pragma once

#include"class_defines.h"

#include<fstream>

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
