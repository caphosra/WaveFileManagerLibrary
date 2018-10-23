#pragma once

#include "class_defines.h"

Int32 convertToInt32(Int8* bytes);
Int16 convertToInt16(Int8* bytes);

#if WFM_CAN_USE_TEMPLATE
/// <summary>
/// The arrays are same ?
/// </summary>
template<typename T>
bool sequenceEqual(T* a, T* b, int count);
#else
/// <summary>
/// The arrays are same ?
/// </summary>
bool sequenceEqual(Int8* a, Int8* b, int count);
#endif

