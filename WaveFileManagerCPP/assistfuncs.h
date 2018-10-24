#pragma once

#include "class_defines.h"

#ifndef WAVEFILE_API
	#define WAVEFILE_API 
#endif

extern "C"
{
	Int32 WAVEFILE_API convertToInt32(Int8* bytes);
	Int16 WAVEFILE_API convertToInt16(Int8* bytes);

	/// <summary>
	/// The arrays are same ?
	/// </summary>
	bool WAVEFILE_API sequenceEqual(Int8* a, Int8* b, int count);
}
