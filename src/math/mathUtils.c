#include "mathUtils.h"

float clamp(inputVal, minVal, maxVal) //Clamps a vlue from a minimim to a maxium
{
	return (inputVal < minVal ? minVal : inputVal > maxVal ? maxVal : inputVal); //? represents if
}

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}
