# WaveFileManagerLibrary
Using this library, you can create simple wave file quickly.

## Description

With this, you can write code to create audio files quickly.:dash: And you can create audio files without struggle with binary files!:ok_hand:  
Even if you are not good at file operations, you can write code intuitively!:smile:  

This library was originally developed for C#, but now, it is developed for C++.
This project has been reborn for C++!:clap:
It means this library doesn't depend on .NET framework!:relaxed:
If you want to use this on C#, you can download C# edition in the release page but it maybe not latest version.

## Requirement

This project depends on nothing.

## Usage

If you want to make wavefile, you can do only following code with WaveFileManager.
```C++
//#include "wavefile_manager.h"

//Declare variables
WaveFileManager waveFile;
MusicPropertyMonaural16bit prop16bit;
short soundData[44100 * 2];

//Generate sound data (440Hz)
GenerateSoundMonaural16bits(soundData, 440);
prop16bit = GenerateMonaural16bits(soundData, 44100 * 2);

//Create WaveFile
waveFile.CreateFile("C:\\capra.wav", prop16bit);
```

## Install

1. Go to [ReleasePage](https://github.com/capra314cabra/WaveFileManagerLibrary/releases) and
download the files.
(or go to [GitHome](https://github.com/capra314cabra/WaveFileManagerLibrary)and download the zipfile)
2. Include the files to your project.

Only this.

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
