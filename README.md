# WaveFileManagerLibrary

Using this library, you can quickly write code to create simple wave file.

## Description

With this, you can write code to create audio files quickly.:dash: And you can create audio files without struggle with binary files!:ok_hand:  
Even if you are not good at file operations, you can write code intuitively!:smile:  

This library was originally developed for C#, but now, it is developed for C++.
This project has been reborn for C++!:clap:
It means this library doesn't depend on .NET framework!:relaxed:
If you want to use this on C#, you can download C# edition in the release page but it maybe not latest version.

## Requirement

This project depends on nothing (C++ edition)  
This project depends on .NET framework or .NET Core (C# edtion)

## Usage

I will show an example about this.
A detailed explanation about this can be seen on the site(Sorry, it's preparing now).

### On C++

Following code with WaveFileManager works that create wave file.
```C++
//#include "wavefile_manager.h"

//Declare variables
MusicProperty musicProperty;
WAVEFORMATEX format;
unsigned char data[44100 * 6];

//Generate sound data (C4 - 3 second)
generateSoundMonaural16bits(data, 44100 * 6, C4, 44100, 15000);

//Generate contents of WaveFile
generateWAVEFORMATEX(&format, MONAURAL_16BITS);
generateMusicProperty(&musicProperty, &format, MONAURAL_16BITS, data, 44100 * 6);
	

createFile("C:\\capra.wav", &musicProperty);
```

### On C#

Following code with WaveFileManager works that create wave file.(This code behaves just like above code.)
```C#
//using WFM;

//Declare variables
MusicProperty musicProperty = new MusicProperty();
WAVEFORMATEX format = new WAVEFORMATEX();
byte[] itibyou = new byte[44100 * 6];

//Generate sound data (C4 - 3 second)
WaveFileManager.GenerateSoundMonaural16bits(itibyou, Hertz.C4, 44100, 15000);

//Generate contents of WaveFile
WaveFileManager.GenerateWAVEFORMATEX(ref format, EDataType.MONAURAL_16BITS);
WaveFileManager.GenerateMusicProperty(ref musicProperty, format, EDataType.MONAURAL_16BITS,itibyou);

//Create WaveFile
WaveFileManager.CreateFile("C:\\capra.wav", musicProperty);
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
