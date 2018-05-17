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
        public static short[] GenerateSoundMonaural16bits(double herth, int samplesPerSec = 44100)
        {
            List<short> list = new List<short>();
            for (int i = 0; i < samplesPerSec * 2; i++)
            {
                list.Add((short)(Math.Sin(i / (double)samplesPerSec * 2d * Math.PI * herth) * 30000));
            }
            return list.ToArray();
        }

        public static void CreateWaveFile(string path, short[] data)
            => CreateFile(path, GenerateMonaural16bits(data));

        public static void CreateWaveFile(string path, byte[] data)
            => CreateFile(path, GenerateMonaural8bits(data));
    }
}
