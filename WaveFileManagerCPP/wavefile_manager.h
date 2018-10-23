#pragma once

#if WAVEFILE_EXPORT
	#define WAVEFILE_API __declspec(dllexport)
#elif WAVEFILE_IMPORT
	#define WAVEFILE_API __declspec(dllimport)
#else
	#define WAVEFILE_API
#endif

#ifndef WITHOUT_ASSIST_FUNCS
    #include"sound_generator.h"
#endif

#ifndef WITHOUT_INSTANCE_GENERATOR
	#include"instance_generator.h"
#endif
