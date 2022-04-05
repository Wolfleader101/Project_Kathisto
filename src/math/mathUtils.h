#pragma once
#include <math.h>
#include "math/Vector.h" //Includes definitions for Vectors

float lerp(float a, float b, float t);

Vector3 ForwardVector(Vector3 vecFromPos, Vector3 vecToPos); //Returns a Forward Vector

Vector3 CrossProduct(Vector3 v1, Vector3 v2); //Returns the Cross Produc of two vectors

Vector3 NormalizeVector(Vector3 v1); //Returns a Normalized Vector

float CalculateMagnitude(Vector3 v1); //Returns the magnitude (Length) of a Vector

//////////////////////////////
////	REFERENCES
//////////////////////////////

// http://www.fundza.com/vectors/normalize/
//		- Used for calculating Magnitude and Normalizing of vectors
// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
//		- Used for calculating the forward vector and cross product