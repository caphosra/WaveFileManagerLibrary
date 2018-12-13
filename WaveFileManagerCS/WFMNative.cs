using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace WFM
{
    namespace Native
    {
        public static class WaveFileManagerNative
        {
            [DllImport("wavefile_manager.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
            public static extern void createFile(string path, IntPtr prop);

            [DllImport("wavefile_manager.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
            public static extern void generateWAVEFORMATEX(IntPtr format, EDataType type);

            [DllImport("wavefile_manager.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
            public static extern void generateMusicProperty(IntPtr mpm, IntPtr waveFormat, EDataType type, IntPtr data, UInt32 size);
        }
    }
}
