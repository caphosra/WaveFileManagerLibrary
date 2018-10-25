#pragma once

#if defined WAVEFILE_EXPORT
	#define WAVEFILE_API __declspec(dllexport)
#elif defined WAVEFILE_IMPORT
	#define WAVEFILE_API __declspec(dllimport)
#else
	#define WAVEFILE_API
#endif

#include "class_defines.h"
#include "assistfuncs.h"
#include "wavefile_stream.h"

#ifndef WITHOUT_ASSIST_FUNCS
    #include"sound_generator.h"
#endif

#ifndef WITHOUT_INSTANCE_GENERATOR
	#include"instance_generator.h"
#endif
