#include "assistfuncs.h"

#pragma region ConvertFromArrayToNumber

Int32 convertToInt32(Int8* bytes)
{
	Int32 i;
	memcpy(&i, bytes, sizeof(Int32));
	return i;

}

Int16 convertToInt16(Int8* bytes)
{
	Int16 i;
	memcpy(&i, bytes, sizeof(Int16));
	return i;
}

#pragma endregion

/// <summary>
/// The arrays are same ?
/// </summary>
template<typename T>
bool sequenceEqual(T* a, T* b, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (a[i] != b[i]) return false;
	}
	return true;
}

/// <summary>
/// The arrays are same ?
/// </summary>
bool sequenceEqual(Int8* a, Int8* b, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (a[i] != b[i]) return false;
	}
	return true;
}
