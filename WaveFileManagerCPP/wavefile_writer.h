#pragma once

#include"class_defines.h"

/// <summary>
/// Create simple wave file.
/// </summary>
void WaveFileManager::createFile(std::string path, MusicPropertyMonaural16bit* prop)
{
	std::fstream fs(path, std::ios::out | std::ios::binary);

	writeMusicProperty(&fs, prop);

	WAVEFORMATEX format = prop->m_WaveFormatEx;

	writeWAVEFORMATEX(&fs, &format);

	fs.write(data_CONST, 4);

	MusicDataMonaural16bit musicData = prop->m_MusicData;
	{
		//It means nothing.
		Int8 int8array[4];

		memcpy(int8array, &musicData.m_DataSize, sizeof(Int32));
		fs.write(int8array, sizeof(Int32));

#pragma warning(push)
#pragma warning(disable:4018)
		for (int i = 0; i < musicData.m_Data.size(); i++)
		{
			Int16 data = musicData.m_Data[i];
			memcpy(int8array, &data, sizeof(Int16));
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
void WaveFileManager::createFile(std::string path, MusicPropertyMonaural8bit* prop)
{
	std::fstream fs(path, std::ios::out | std::ios::binary);

	writeMusicProperty(&fs, prop);

	WAVEFORMATEX format = prop->m_WaveFormatEx;

	writeWAVEFORMATEX(&fs, &format);

	fs.write(data_CONST, 4);

	MusicDataMonaural8bit musicData = prop->m_MusicData;
	{
		// It means nothing.
		Int8 int8array[4];

		memcpy(int8array, &musicData.m_DataSize, sizeof(Int32));
		fs.write(int8array, 4);

#pragma warning(push)
#pragma warning(disable:4018)
		for (int i = 0; i < musicData.m_Data.size(); i++)
		{
			Int8 data = musicData.m_Data[i];
			memcpy(int8array, &data, sizeof(Int8));
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
void WaveFileManager::writeMusicProperty(std::fstream* fs, MusicProperty* prop)
{
	Int8 i[4];

	fs->write(RIFF, 4);

	memcpy(i, &(prop->m_FileSize), sizeof(Int32));
	fs->write(i, 4);

	fs->write(WAVE, 4);

	fs->write(fmt, 4);

	memcpy(i, &(prop->m_PCMWAVEFORMAT_Size), sizeof(Int32));
	fs->write(i, 4);
}

void WaveFileManager::writeWAVEFORMATEX(std::fstream* fs, WAVEFORMATEX* format)
{
	Int8 i[4];

	memcpy(i, &(format->wFormatTag), sizeof(Int16));
	fs->write(i, 2);

	memcpy(i, &(format->nChannels), sizeof(UInt16));
	fs->write(i, 2);

	memcpy(i, &(format->nSamplesPerSec), sizeof(UInt32));
	fs->write(i, 4);

	memcpy(i, &(format->nAvgBytePerSec), sizeof(UInt32));
	fs->write(i, 4);

	memcpy(i, &(format->nBlockAlign), sizeof(UInt16));
	fs->write(i, 2);

	memcpy(i, &(format->wBitsPerSample), sizeof(UInt16));
	fs->write(i, 2);
}
