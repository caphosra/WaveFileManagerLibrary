using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WaveFileManager
{
    public partial class WaveFileManager
    {
        public static MusicPropertyMonaural16bit GenerateMonaural16bits(short[] data)
        {
            MusicPropertyMonaural16bit w = new MusicPropertyMonaural16bit();

            w.m_FileSize = 36 + data.Length * 2;
            w.m_PCMWAVEFORMAT_Size = 16;
            w.m_WaveFormatEx = WAVEFORMATEX.Monaural16bitsDefault;
            var data16bit = new MusicDataMonaural16bit();
            data16bit.m_DataSize = data.Length * 2;
            data16bit.m_Data = data;
            w.m_MusicData = data16bit;

            return w;
        }

        public static MusicPropertyMonaural8bit GenerateMonaural8bits(byte[] data)
        {
            MusicPropertyMonaural8bit w = new MusicPropertyMonaural8bit();

            w.m_FileSize = 36 + data.Length;
            w.m_PCMWAVEFORMAT_Size = 16;
            w.m_WaveFormatEx = WAVEFORMATEX.Monaural8bitsDefault;
            var data8bit = new MusicDataMonaural8bit();
            data8bit.m_DataSize = data.Length;
            data8bit.m_Data = data;
            w.m_MusicData = data8bit;

            return w;
        }
    }
}
