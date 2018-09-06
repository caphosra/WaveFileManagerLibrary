#include"class_defines.h"

#include<fstream>

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
