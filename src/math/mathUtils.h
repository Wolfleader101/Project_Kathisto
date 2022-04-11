#pragma once
#include <math.h>

#define PI_MATH 3.14159265359 //Value of Pi

float clamp(inputVal, minVal, maxVal); //Clamps a vlue from a minimim to a maxium

float lerp(float a, float b, float t);

//////////////////////////////
////	REFERENCES
//////////////////////////////

// https://www.studytonight.com/c/operators-in-c.php
//		- Information on the Ternary (Conditional) ? Operator
// https://news.ycombinator.com/item?id=16410339
//		- Used to create the Clamp function