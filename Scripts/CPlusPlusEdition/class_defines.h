#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<fstream>

typedef int Int32;
typedef short Int16;
typedef char Int8;
typedef unsigned int UInt32;
typedef unsigned short UInt16;

#define C4 261.626
#define D4 293.665
#define E4 329.628
#define F4 349.228
#define G4 391.995
#define A4 440.000
#define B4 493.883

#ifndef WAVEFILE_API
	#define WAVEFILE_API 
#endif

extern "C"
{
	/// <summary>
	/// Define the file type
	/// </summary>
	enum EDataType
	{
		MONAURAL_8BITS = 1,
		MONAURAL_16BITS = 2,

	};

	struct WAVEFORMATEX
	{
	public:
		Int16 wFormatTag;
		UInt16 nChannels;
		UInt32 nSamplesPerSec;
		UInt32 nAvgBytePerSec;
		UInt16 nBlockAlign;
		UInt16 wBitsPerSample;
	};

	struct MusicProperty
	{
	public:
		Int32 m_FileSize;
		Int32 m_PCMWAVEFORMAT_Size;
		WAVEFORMATEX m_WaveFormatEx;

		Int32 m_DataSize;
		EDataType m_DataType;
		Int8* m_Data;
	};
}
