/*
 * 
 * 16bitモノラル対応
 * サンプリング周波数：44,100Hz
 * データ転送のための最小単位：2byte
 * サンプリングビット：16bits
 * 
 * 参考：http://norte.coron.jp/sound/wav01.html
 * 
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace WaveFileManager
{
    public partial class WaveFileManager
    {
        //
        // 常に同じ値のもの
        //
        public static readonly byte[] RIFF = new byte[] { 0x52, 0x49, 0x46, 0x46 };
        public static readonly byte[] WAVE = new byte[] { 0x57, 0x41, 0x56, 0x45 };
        public static readonly byte[] fmt = new byte[] { 0x66, 0x6D, 0x74, 0x20 };
        public static readonly byte[] data = new byte[] { 0x64, 0x61, 0x74, 0x61 };

        /// <summary>
        /// Load wave file that is made by this program.
        /// </summary>
        [Obsolete]
        public static MusicPropertyMonaural16bit LoadFileMonaural16bits(string path)
        {
            MusicPropertyMonaural16bit property = new MusicPropertyMonaural16bit();

            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read);

            byte[] byte_16 = new byte[2];
            byte[] byte_32 = new byte[4];

            #region RIFF(捨てる)

            fs.Read(byte_32, 0, 4);

            if (!Enumerable.SequenceEqual(byte_32, RIFF))
            {
                throw new ArgumentException("It's not RIFF format file.");
            }

            #endregion

            #region ファイルのサイズ

            fs.Read(byte_32, 0, 4);

            property.m_FileSize = ConvertToInt32(byte_32);

            #endregion

            #region WAVE(捨てる)

            fs.Read(byte_32, 0, 4);

            if (!Enumerable.SequenceEqual(byte_32, WAVE))
            {
                throw new ArgumentException("It's not WAVE file.");
            }

            #endregion

            #region  fmt (捨てる)

            fs.Read(byte_32, 0, 4);

            if (!Enumerable.SequenceEqual(byte_32, fmt))
            {
                throw new ArgumentException("It's not WAVE file.");
            }

            #endregion

            #region  PCMWAVEFORMATのサイズ

            fs.Read(byte_32, 0, 4);

            if (ConvertToInt32(byte_32) != 16)
            {
                throw new ArgumentException("It will have unnecessary chank.");
            }

            #endregion

            WAVEFORMATEX format = WAVEFORMATEX.Monaural16bitsDefault;

            #region  フォーマットタグ

            fs.Read(byte_16, 0, 2);

            if (format.wFormatTag != ConvertToInt16(byte_16))
            {
                throw new ArgumentException("It's WAVE file but does not correspond to this. arg=wFormatTag");
            }

            #endregion

            #region チャンネル

            fs.Read(byte_16, 0, 2);

            if (format.nChannels != ConvertToInt16(byte_16))
            {
                throw new ArgumentException("It's WAVE file but does not correspond to this. arg=nChannels");
            }

            #endregion

            #region サンプリング周波数/サンプリングレート

            fs.Read(byte_32, 0, 4);

            if (format.nSamplesPerSec != ConvertToInt32(byte_32))
            {
                throw new ArgumentException("It's WAVE file but does not correspond to this. arg=nSamplesPerSec");
            }

            #endregion

            #region 平均データ転送レート

            fs.Read(byte_32, 0, 4);

            if (format.nAvgBytePerSec != ConvertToInt32(byte_32))
            {
                throw new ArgumentException("It's WAVE file but does not correspond to this. arg=nAvgBytePerSec");
            }

            #endregion

            #region データ転送のための最小単位

            fs.Read(byte_16, 0, 2);

            if (format.nBlockAlign != ConvertToInt16(byte_16))
            {
                throw new ArgumentException("It's WAVE file but does not correspond to this. arg=nBlockAlign");
            }

            #endregion

            #region サンプリングビット

            fs.Read(byte_16, 0, 2);

            if (format.wBitsPerSample != ConvertToInt16(byte_16))
            {
                throw new ArgumentException("It's WAVE file but does not correspond to this. arg=wBitsPerSample");
            }

            #endregion

            #region data(捨てる)

            fs.Read(byte_32, 0, 4);

            if (!Enumerable.SequenceEqual(byte_32, data))
            {
                throw new ArgumentException("It's not WAVE file.");
            }

            #endregion

            MusicDataMonaural16bit musicData = new MusicDataMonaural16bit();

            #region DataSize

            fs.Read(byte_32, 0, 4);

            musicData.m_DataSize = ConvertToInt32(byte_32);

            #endregion

            #region Data

            List<Int16> list = new List<Int16>();

            for (; ; )
            {
                int readSize = fs.Read(byte_16, 0, 2);
                if (readSize < 2)
                    break;
                list.Add(ConvertToInt16(byte_16));
            }

            musicData.m_Data = list.ToArray();

            #endregion

            //閉じる
            fs.Close();

            property.m_WaveFormatEx = format;
            property.m_MusicData = musicData;

            return property;
        }

        /// <summary>
        /// Create simple wave file.
        /// </summary>
        public static void CreateFile(string path, MusicPropertyMonaural16bit prop)
        {
            FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write);

            WriteMusicProperty(fs, prop);

            WAVEFORMATEX format = prop.m_WaveFormatEx;

            WriteWAVEFORMATEX(fs, format);

            fs.Write(data, 0, 4);

            MusicDataMonaural16bit musicData = prop.m_MusicData;

            fs.Write(ConvertToLittleEndian(musicData.m_DataSize), 0, 4);

            foreach (var d in musicData.m_Data)
            {
                fs.Write(ConvertToLittleEndian(d), 0, 2);
            }

            //閉じる
            fs.Close();
        }

        /// <summary>
        /// Create simple wave file.
        /// </summary>
        public static void CreateFile(string path, MusicPropertyMonaural8bit prop)
        {
            FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write);

            WriteMusicProperty(fs, prop);

            WAVEFORMATEX format = prop.m_WaveFormatEx;

            WriteWAVEFORMATEX(fs, format);

            fs.Write(data, 0, 4);

            MusicDataMonaural8bit musicData = prop.m_MusicData;

            fs.Write(ConvertToLittleEndian(musicData.m_DataSize), 0, 4);

            foreach (var d in musicData.m_Data)
            {
                fs.Write(ConvertToLittleEndian(d), 0, 1);
            }

            //閉じる
            fs.Close();
        }

        //
        // privateなメンバー
        //
        private static void WriteMusicProperty(FileStream fs, MusicProperty prop)
        {
            fs.Write(RIFF, 0, 4);

            fs.Write(ConvertToLittleEndian(prop.m_FileSize), 0, 4);

            fs.Write(WAVE, 0, 4);

            fs.Write(fmt, 0, 4);

            fs.Write(ConvertToLittleEndian(prop.m_PCMWAVEFORMAT_Size), 0, 4);
        }

        private static void WriteWAVEFORMATEX(FileStream fs, WAVEFORMATEX format)
        {
            fs.Write(ConvertToLittleEndian(format.wFormatTag), 0, 2);

            fs.Write(ConvertToLittleEndian(format.nChannels), 0, 2);

            fs.Write(ConvertToLittleEndian(format.nSamplesPerSec), 0, 4);

            fs.Write(ConvertToLittleEndian(format.nAvgBytePerSec), 0, 4);

            fs.Write(ConvertToLittleEndian(format.nBlockAlign), 0, 2);

            fs.Write(ConvertToLittleEndian(format.wBitsPerSample), 0, 2);
        }
        
        private static byte[] ConvertToLittleEndian(Int32 int32)
        {
            if (BitConverter.IsLittleEndian)
            {
                return BitConverter.GetBytes(int32);
            }
            else
            {
                byte[] b = BitConverter.GetBytes(int32);
                return b.Reverse().ToArray();
            }
        }

        private static byte[] ConvertToLittleEndian(Int16 int16)
        {
            if (BitConverter.IsLittleEndian)
            {
                return BitConverter.GetBytes(int16);
            }
            else
            {
                byte[] b = BitConverter.GetBytes(int16);
                return b.Reverse().ToArray();
            }
        }

        private static byte[] ConvertToLittleEndian(UInt32 int32)
        {
            if (BitConverter.IsLittleEndian)
            {
                return BitConverter.GetBytes(int32);
            }
            else
            {
                byte[] b = BitConverter.GetBytes(int32);
                return b.Reverse().ToArray();
            }
        }

        private static byte[] ConvertToLittleEndian(UInt16 int16)
        {
            if (BitConverter.IsLittleEndian)
            {
                return BitConverter.GetBytes(int16);
            }
            else
            {
                byte[] b = BitConverter.GetBytes(int16);
                return b.Reverse().ToArray();
            }
        }

        private static Int32 ConvertToInt32(byte[] bytes)
        {
            if (BitConverter.IsLittleEndian)
            {
                return BitConverter.ToInt32(bytes, 0);
            }
            else
            {
                byte[] b = bytes.Reverse().ToArray();
                return BitConverter.ToInt32(bytes, 0);
            }
        }

        private static Int16 ConvertToInt16(byte[] bytes)
        {
            if (BitConverter.IsLittleEndian)
            {
                return BitConverter.ToInt16(bytes, 0);
            }
            else
            {
                byte[] b = bytes.Reverse().ToArray();
                return BitConverter.ToInt16(bytes, 0);
            }
        }

        private static UInt32 ConvertToUInt32(byte[] bytes)
        {
            if (BitConverter.IsLittleEndian)
            {
                return BitConverter.ToUInt32(bytes, 0);
            }
            else
            {
                byte[] b = bytes.Reverse().ToArray();
                return BitConverter.ToUInt32(bytes, 0);
            }
        }

        private static UInt16 ConvertToUInt16(byte[] bytes)
        {
            if (BitConverter.IsLittleEndian)
            {
                return BitConverter.ToUInt16(bytes, 0);
            }
            else
            {
                byte[] b = bytes.Reverse().ToArray();
                return BitConverter.ToUInt16(bytes, 0);
            }
        }
    }
}
