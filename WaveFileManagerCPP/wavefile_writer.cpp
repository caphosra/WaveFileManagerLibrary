#include"class_defines.h"

extern "C"
{
	/// <summary>
	/// Create simple wave file.
	/// </summary>
	void WaveFileManager::createFile(std::string path, MusicProperty* prop)
	{
		Int8 data_CONST[]{ 0x64, 0x61, 0x74, 0x61 };

		std::fstream fs(path, std::ios::out | std::ios::binary);

		writeMusicProperty(&fs, prop);

		WAVEFORMATEX format = prop->m_WaveFormatEx;

		writeWAVEFORMATEX(&fs, &format);

		fs.write(data_CONST, 4);

		switch (prop->m_DataType)
		{
		case MONAURAL_16BITS:
		{
			//It means nothing.
			Int8 int8array[4];

			memcpy(int8array, &(prop->m_DataSize), sizeof(Int32));
			fs.write(int8array, sizeof(Int32));

#pragma warning(push)
#pragma warning(disable:4018)
			for (int i = 0; i < (prop->m_DataSize / sizeof(Int16)); i++)
			{
				Int16 data = ((Int16*)(prop->m_Data))[i];
				memcpy(int8array, &data, sizeof(Int16));
				fs.write(int8array, sizeof(Int16));
			}
#pragma warning(pop)
		}
		break;
		case MONAURAL_8BITS:
		{
			// It means nothing.
			Int8 int8array[4];

			memcpy(int8array, &(prop->m_DataSize), sizeof(Int32));
			fs.write(int8array, 4);

#pragma warning(push)
#pragma warning(disable:4018)
			for (int i = 0; i < (prop->m_DataSize / sizeof(Int8)); i++)
			{
				memcpy(int8array, &(prop->m_Data[i]), sizeof(Int8));
				fs.write(int8array, sizeof(Int8));
			}
#pragma warning(pop)
		}
		break;
		}

		// Close the file stream.
		fs.close();
	}

	//
	// private member
	//
	void WaveFileManager::writeMusicProperty(std::fstream* fs, MusicProperty* prop)
	{
		Int8 RIFF[]{ 0x52, 0x49, 0x46, 0x46 };
		Int8 WAVE[]{ 0x57, 0x41, 0x56, 0x45 };
		Int8 fmt[]{ 0x66, 0x6D, 0x74, 0x20 };

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
}
