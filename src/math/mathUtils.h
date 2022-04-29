#pragma once
#include <math.h>

#define PI_CONST 3.141592653589793238 //Value of Pi
#define RAD2DEG 0.01745329252 //Number of Radians in 1 Degree
#define DEG2RAD 57.295779513 //Number of Degrees in 1 Radian

float clamp(inputVal, minVal, maxVal); //Clamps a vlue from a minimim to a maxium

float lerp(float a, float b, float t);

//////////////////////////////
////	REFERENCES
//////////////////////////////

// https://www.studytonight.com/c/operators-in-c.php
//		- Information on the Ternary (Conditional) ? Operator
// https://news.ycombinator.com/item?id=16410339
//		- Used to create the Clamp function
// https://c-for-dummies.com/blog/?p=4139
//		- Degrees to Radians to Degrees