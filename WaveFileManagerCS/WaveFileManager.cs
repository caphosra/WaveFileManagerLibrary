using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using WFM.Native;

namespace WFM
{
    public static class Hertz
    {
        public const double C4 = 261.626;
        public const double D4 = 293.665;
        public const double E4 = 329.628;
        public const double F4 = 349.228;
        public const double G4 = 391.995;
        public const double A4 = 440.000;
        public const double B4 = 493.883;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct MusicProperty
    {
        public int m_FileSize;
        public int m_PCMWAVEFORMAT_Size;
        public WAVEFORMATEX m_WaveFormatEx;

        public int m_DataSize;
        // EDataType
        public int m_DataType;
        public IntPtr m_Data;
    }

    public enum EDataType
    {
        MONAURAL_8BITS = 1,
        MONAURAL_16BITS = 2, 
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct WAVEFORMATEX
    {
        public short wFormatTag;
        public ushort nChannels;
        public uint nSamplesPerSec;
        public uint nAvgBytePerSec;
        public ushort nBlockAlign;
        public ushort wBitsPerSample;
    };

    public static class WaveFileManager
    {
        public static void CreateFile(string path, MusicProperty prop)
        {
            IntPtr propPointer = Marshal.AllocHGlobal(Marshal.SizeOf(prop));
            Marshal.StructureToPtr(prop, propPointer, false);
            WaveFileManagerNative.createFile(path, propPointer);
            Marshal.FreeHGlobal(propPointer);
        }

        public static void GenerateWAVEFORMATEX(ref WAVEFORMATEX format, EDataType dataType)
        {
            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(format));
            Marshal.StructureToPtr(format, ptr, false);
            WaveFileManagerNative.generateWAVEFORMATEX(ptr, dataType);
            format = Marshal.PtrToStructure<WAVEFORMATEX>(ptr);
            Marshal.FreeHGlobal(ptr);
        }

        public static void GenerateMusicProperty(ref MusicProperty prop, WAVEFORMATEX format, EDataType type, byte[] data)
        {
            IntPtr propPtr = Marshal.AllocHGlobal(Marshal.SizeOf(prop));
            Marshal.StructureToPtr(prop, propPtr, false);

            IntPtr formatPtr = Marshal.AllocHGlobal(Marshal.SizeOf(format));
            Marshal.StructureToPtr(format, formatPtr, false);

            IntPtr ptr = Marshal.AllocHGlobal(data.Length);
            Marshal.Copy(data, 0, ptr, data.Length);

            WaveFileManagerNative.generateMusicProperty(propPtr, formatPtr, type, ptr, (uint)data.Length);

            prop = Marshal.PtrToStructure<MusicProperty>(propPtr);

            Marshal.FreeHGlobal(propPtr);
            Marshal.FreeHGlobal(formatPtr);

            // It should be free, but can't do that.
            // This bug will be fixed.
            // Marshal.FreeHGlobal(ptr);
        }

        public static void GenerateSoundMonaural16bits(byte[] data, double herth, int samplesPerSec = 44100, int volume = 30000)
        {
            var dataPtr = Marshal.AllocHGlobal(data.Length);
            Marshal.Copy(data, 0, dataPtr, data.Length);

            WaveFileManagerNative.generateSoundMonaural16bits(dataPtr, (uint)data.Length, herth, samplesPerSec, volume);

            Marshal.Copy(dataPtr, data, 0, data.Length);
        }
    }
}
