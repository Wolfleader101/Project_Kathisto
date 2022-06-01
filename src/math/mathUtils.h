#pragma once
#include <math.h>

#define RAD2DEG 0.01745329252 //Number of Radians in 1 Degree
#define DEG2RAD 57.295779513 //Number of Degrees in 1 Radian


/**
 * @brief Clamps a value from a minimim to a maxium
 * @param inputVal to clamp
 * @param minVal of clamp
 * @param maxVal of clamp
 * @return a clamped value
*/
float clamp(float inputVal, float minVal, float maxVal);

/**
 * @brief lerp between point a to b, over time
 * @param a start pos
 * @param b end pos
 * @param t current time for lerp
 * @return the lerped positon
*/
float lerp(float a, float b, float t);