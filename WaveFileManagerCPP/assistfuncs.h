#pragma once

#include "class_defines.h"

extern "C"
{
	Int32 convertToInt32(Int8* bytes);
	Int16 convertToInt16(Int8* bytes);

	/// <summary>
	/// The arrays are same ?
	/// </summary>
	bool sequenceEqual(Int8* a, Int8* b, int count);
}
