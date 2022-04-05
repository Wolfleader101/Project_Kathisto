#include "mathUtils.h"

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

Vector3 ForwardVector(Vector3 vecFromPos, Vector3 vecToPos) //Returns a Forward Vector
{
	Vector3 tmpVec = { 0, 0, 0 }; //Temporary vector for calculations
	Vector3 tmpVecReturn = { 0, 0, 0 }; //Temporary vector for calculations, returned

	tmpVec.x = vecFromPos.x - vecToPos.x; //Calculates the X value of the Forward Vector
	tmpVec.y = vecFromPos.y - vecToPos.y; //Calculates the Y value of the Forward Vector
	tmpVec.z = vecFromPos.z - vecToPos.z; //Calculates the Z value of the Forward Vector

	tmpVecReturn = NormalizeVector(tmpVec); //Calculates the normalized version of the forward vector

	return(tmpVecReturn);
}

Vector3 CrossProduct(Vector3 v1, Vector3 v2) //Returns the Cross Produc of two vectors
{
	Vector3 tmpVec = {0, 0, 0}; //Temporary vector for calculations

	tmpVec.x = (v1.y * v2.z) - (v1.z * v2.y); //Calculates the X Variable of the new vector
	tmpVec.y = (v1.z * v2.x) - (v1.x * v2.z); //Calculates the Y Variable of the new vector
	tmpVec.z = (v1.x * v2.y) - (v1.y * v2.x); //Calculates the Z Variable of the new vector
	
	return(tmpVec);
}

Vector3 NormalizeVector(Vector3 v1) //Returns a Normalized Vector
{
	float tmpMagnitude = 0.0f; //Temporary vector for calculations
	Vector3 tmpVec = { 0, 0, 0 }; //Temporary vector for calculations

	tmpMagnitude = CalculateMagnitude(v1); //Calculates the Mangitude of the input vector

	tmpVec = v1; //Sets tmpVec equal to the input vector

	tmpVec.x = tmpVec.x / tmpMagnitude; //Calculates the normalized X value
	tmpVec.y = tmpVec.y / tmpMagnitude; //Calculates the normalized Y value
	tmpVec.z = tmpVec.z / tmpMagnitude; //Calculates the normalized Z value

	return(tmpVec);
}

float CalculateMagnitude(Vector3 v1) //Returns the magnitude (Length) of a Vector
{
	float tmpMagnitude = 0.0f; //Temporary vector for calculations
	
	return(tmpMagnitude = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z)));
}