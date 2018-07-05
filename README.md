# WaveFileManagerLibrary
Using this library, you can create simple wave file quickly.

## Description

With this you can write code to quickly create audio files. You can create audio files without struggle with binary files.
Even if you are not good at file operations, you can write code intuitively.
Since this library was originally developed for C#, there may be problems with the porting process to C++.

## Requirement

C# library depends on .NET framework.

## Usage

```C++
//#include "WaveFileManager.h"
WaveFileManager waveFile;
MusicPropertyMonaural16bit prop16bit;
short soundData[44100 * 2];
//Generate sound data (440Hz)
GenerateSoundMonaural16bits(soundData, 440);
prop16bit = GenerateMonaural16bits(soundData, 44100 * 2);
waveFile.CreateFile("C:\\capra.wav", prop16bit);
```

## Install

Go to [ReleasePage](https://github.com/capra314cabra/WaveFileManagerLibrary/releases) or Download [Code](https://github.com/capra314cabra/WaveFileManagerLibrary)

## Contribution

1. Fork it
2. Create your feature branch (git checkout -b my-new-feature)
3. Commit your changes (git commit -am 'Add some feature')
4. Push to the branch (git push origin my-new-feature)
5. Create new Pull Request

## Licence

[MIT](https://github.com/capra314cabra/WaveFileManagerLibrary/blob/master/LICENSE)

## Author

[capra314cabra](https://github.com/capra314cabra)
