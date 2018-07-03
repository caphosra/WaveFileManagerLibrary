#pragma once

#include"DefineClass.h"

#include<fstream>

//
// ��ɓ����l�̂���
//
Int8 RIFF[]{ 0x52, 0x49, 0x46, 0x46 };
Int8 WAVE[]{ 0x57, 0x41, 0x56, 0x45 };
Int8 fmt[]{ 0x66, 0x6D, 0x74, 0x20 };
Int8 data_CONST[]{ 0x64, 0x61, 0x74, 0x61 };

/// <summary>
/// Load wave file that is made by this program.
/// </summary>
MusicPropertyMonaural16bit WaveFileManager::LoadFileMonaural16bits(string path)
{
	MusicPropertyMonaural16bit property;

	ifstream ifs(path, ios::in | ios::binary);

	Int8 byte_16[2];
	Int8 byte_32[4];

	#pragma region RIFF(�̂Ă�)

	ifs.read(byte_32, 4);

	if (!SequenceEqual(byte_32, RIFF, 4))
	{
		throw "It's not RIFF format file.";
	}

	#pragma endregion

	#pragma region �t�@�C���̃T�C�Y

	ifs.read(byte_32, 4);

	property.m_FileSize = ConvertToInt32(byte_32);

	#pragma endregion

	#pragma region WAVE(�̂Ă�)

	ifs.read(byte_32, 4);

	if (!SequenceEqual(byte_32, WAVE, 4))
	{
		throw "It's not WAVE file.";
	}

	#pragma endregion

	#pragma region  fmt(�̂Ă�)

	ifs.read(byte_32, 4);

	if (!SequenceEqual(byte_32, fmt, 4))
	{
		throw "It's not WAVE file.";
	}

	#pragma endregion

	#pragma region  PCMWAVEFORMAT�̃T�C�Y

	ifs.read(byte_32, 4);

	if (ConvertToInt32(byte_32) != 16)
	{
		throw "It will have unnecessary chank.";
	}

	#pragma endregion

	WAVEFORMATEX format;
	format = format.GetMonaural16bitsDefault;

	#pragma region �t�H�[�}�b�g�^�O

	ifs.read(byte_16, 2);

	if (format.wFormatTag != ConvertToInt16(byte_16))
	{
		throw "It's WAVE file but does not correspond to this. arg=wFormatTag";
	}

	#pragma endregion

	#pragma region �`�����l��

	ifs.read(byte_16, 2);

	if (format.nChannels != ConvertToInt16(byte_16))
	{
		throw "It's WAVE file but does not correspond to this. arg=nChannels";
	}

	#pragma endregion

	#pragma region �T���v�����O���g�� / �T���v�����O���[�g

	ifs.read(byte_32, 4);

	if (format.nSamplesPerSec != ConvertToInt32(byte_32))
	{
		throw "It's WAVE file but does not correspond to this. arg=nSamplesPerSec";
	}

	#pragma endregion

	#pragma region ���σf�[�^�]�����[�g

	ifs.read(byte_32, 4);

	if (format.nAvgBytePerSec != ConvertToInt32(byte_32))
	{
		throw "It's WAVE file but does not correspond to this. arg=nAvgBytePerSec";
	}

	#pragma endregion

	#pragma region �f�[�^�]���̂��߂̍ŏ��P��

	ifs.read(byte_16, 2);

	if (format.nBlockAlign != ConvertToInt16(byte_16))
	{
		throw "It's WAVE file but does not correspond to this. arg=nBlockAlign";
	}

	#pragma endregion

	#pragma region �T���v�����O�r�b�g

	ifs.read(byte_16, 2);

	if (format.wBitsPerSample != ConvertToInt16(byte_16))
	{
		throw "It's WAVE file but does not correspond to this. arg=wBitsPerSample";
	}

	#pragma endregion

	#pragma region data(�̂Ă�)

	ifs.read(byte_32, 4);

	if (!SequenceEqual(byte_32, data_CONST, 4))
	{
		throw "It's not WAVE file.";
	}

	#pragma endregion

	MusicDataMonaural16bit musicData;

	#pragma region DataSize

	ifs.read(byte_32, 4);

	musicData.m_DataSize = ConvertToInt32(byte_32);

	#pragma endregion

	#pragma region Data

	vector<Int16> list;

	for (; ; )
	{
		ifs.read(byte_16, 2);
		if (ifs.eof())
			break;
		list.push_back(ConvertToInt16(byte_16));
	}

	musicData.m_Data = list;

	#pragma endregion

	//����
	ifs.close();

	property.m_WaveFormatEx = format;
	property.m_MusicData = musicData;

	return property;
}

/// <summary>
/// Create simple wave file.
/// </summary>
void WaveFileManager::CreateFile(string path, MusicPropertyMonaural16bit prop)
{
	fstream fs(path, ios::out | ios::binary);

	WriteMusicProperty(&fs, prop);

	WAVEFORMATEX format = prop.m_WaveFormatEx;

	WriteWAVEFORMATEX(&fs, format);

	fs.write(data_CONST, 4);

	MusicDataMonaural16bit musicData = prop.m_MusicData;
	{
		//�ėp�z��
		Int8 int8array[4];

		ConvertToLittleEndian(int8array, musicData.m_DataSize);
		fs.write(int8array, sizeof(Int32));

		for (int i = 0; i < musicData.m_Data.size(); i++)
		{
			ConvertToLittleEndian(int8array, musicData.m_Data[i]);
			fs.write(int8array, sizeof(Int16));
		}
	}

	//����
	fs.close();
}

/// <summary>
/// Create simple wave file.
/// </summary>
void WaveFileManager::CreateFile(string path, MusicPropertyMonaural8bit prop)
{
	fstream fs(path, ios::out | ios::binary);

	WriteMusicProperty(&fs, prop);

	WAVEFORMATEX format = prop.m_WaveFormatEx;

	WriteWAVEFORMATEX(&fs, format);

	fs.write(data_CONST, 4);

	MusicDataMonaural8bit musicData = prop.m_MusicData;
	{
		//�ėp�z��
		Int8 int8array[4];

		ConvertToLittleEndian(int8array, musicData.m_DataSize);
		fs.write(int8array, 4);

		for (int i = 0; i < musicData.m_Data.size(); i++)
		{
			ConvertToLittleEndian(int8array, musicData.m_Data[i]);
			fs.write(int8array, sizeof(Int8));
		}
	}

	//����
	fs.close();
}

//
// private�ȃ����o�[
//
void WaveFileManager::WriteMusicProperty(fstream* fs, MusicProperty prop)
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

void WaveFileManager::WriteWAVEFORMATEX(fstream* fs, WAVEFORMATEX format)
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
