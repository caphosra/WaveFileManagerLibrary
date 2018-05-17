using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WaveFileManager
{
    public class MusicProperty
    {
        public Int32 m_FileSize;
        public Int32 m_PCMWAVEFORMAT_Size;
        public WAVEFORMATEX m_WaveFormatEx;
    }

    public class MusicPropertyMonaural16bit : MusicProperty
    {
        public MusicDataMonaural16bit m_MusicData;
    }

    public class MusicPropertyMonaural8bit : MusicProperty
    {
        public MusicDataMonaural8bit m_MusicData;
    }

    public struct MusicDataMonaural16bit
    {
        public Int32 m_DataSize;
        public Int16[] m_Data;
    }

    public struct MusicDataMonaural8bit
    {
        public Int32 m_DataSize;
        public byte[] m_Data;
    }

    public class WAVEFORMATEX
    {
        public Int16 wFormatTag;
        public UInt16 nChannels;
        public UInt32 nSamplesPerSec;
        public UInt32 nAvgBytePerSec;
        public UInt16 nBlockAlign;
        public UInt16 wBitsPerSample;

        /// <summary>
        /// Monaural 16bits 44100Hz
        /// </summary>
        public static WAVEFORMATEX Monaural16bitsDefault
        {
            get
            {
                WAVEFORMATEX format = new WAVEFORMATEX();
                format.wFormatTag = 1;
                format.nChannels = 1;
                format.nSamplesPerSec = 44100;
                format.nAvgBytePerSec = 88200;
                format.nBlockAlign = 2;
                format.wBitsPerSample = 16;
                return format;
            }
        }

        /// <summary>
        /// Monaural 8bits 44100Hz
        /// </summary>
        public static WAVEFORMATEX Monaural8bitsDefault
        {
            get
            {
                WAVEFORMATEX format = new WAVEFORMATEX();
                format.wFormatTag = 1;
                format.nChannels = 1;
                format.nSamplesPerSec = 44100;
                format.nAvgBytePerSec = 44100;
                format.nBlockAlign = 1;
                format.wBitsPerSample = 8;
                return format;
            }
        }
    }
}
