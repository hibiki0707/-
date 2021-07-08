#include "Utility.h"

float Utility::Lerp(float start, float end, float t)
{
	// üŒ`•âŠÔ
	float ret = start;
	ret += t * (end - start);
    return ret;
}
