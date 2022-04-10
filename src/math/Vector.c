#include "Vector.h"

Vector2 EmptyVec2()
{
	return (Vector2){0.0f, 0.0f};
}

Vector3 EmptyVec3(){

	return (Vector3){0.0f, 0.0f, 0.0f};
}

Quaternion EmptyQuaternion() 
{
	return (Quaternion) { 0.0f, 0.0f, 0.0f, 0.0f };
}

Vector2 ArrayToVec2(const float arr[2])
{
	return (Vector2) { arr[0], arr[1] };
}

Vector3 ArrayToVec3(const float arr[3])
{
	return (Vector3) { arr[0], arr[1], arr[2] };
}

RGBA ArrayToRGBA(const float arr[4])
{
	return (RGBA) { arr[0], arr[1], arr[2], arr[3] };
}

float* Vec2ToArray(const Vector2 vec)
{
	float* arr = malloc(2 * sizeof(float));
	if (arr != NULL)
	{
		arr[0] = vec.x;
		arr[1] = vec.y;
	}


	return arr;
}

float* Vec3ToArray(const Vector3 vec)
{
	float* arr = malloc(3 * sizeof(float));
	if (arr != NULL)
	{
		arr[0] = vec.x;
		arr[1] = vec.y;
		arr[2] = vec.z;
	}

	return arr;
}

float* RGBAToArray(const RGBA vec)
{
	float* arr = malloc(4 * sizeof(float));
	if (arr != NULL)
	{
		arr[0] = vec.r;
		arr[1] = vec.g;
		arr[2] = vec.b;
		arr[3] = vec.a;
	}

	return arr;
}

float* RGBAArrayToArray(const RGBA* vecArr, size_t length)
{
	if (length <= 0) length = 1;
	float* arr = malloc(4 * length * sizeof(float));
	if (arr != NULL)
	{
		for (size_t i = 0; i < length; i++)
		{
			arr[0 + (i * 4)] = vecArr[i].r;
			arr[1 + (i * 4)] = vecArr[i].g;
			arr[2 + (i * 4)] = vecArr[i].b;
			arr[3 + (i * 4)] = vecArr[i].a;
		}
	}
	return arr;
}

float Vec2Length(Vector2 vec)
{
	return sqrt(((double)vec.x * vec.x) + ((double)vec.y * vec.y));
}

float Vec3Length(Vector3 vec)
{
	return sqrt(((double)vec.x * vec.x) + ((double)vec.y * vec.y) + ((double)vec.z * vec.z));
}

Vector2 Vec2Normalize(Vector2 vec)
{
	float length = Vec2Length(vec);
	return (Vector2) { vec.x / length, vec.y / length };
}

Vector3 Vec3Normalize(Vector3 vec)
{
	float length = Vec3Length(vec);
	return (Vector3) { vec.x / length, vec.y / length, vec.z / length };
}

Vector2 Vec2ScalarMultiply(Vector2 vec, float scalar)
{
	return (Vector2) { vec.x * scalar, vec.y * scalar };
}

Vector3 Vec3ScalarMultiply(Vector3 vec, float scalar)
{
	return (Vector3) { vec.x * scalar, vec.y * scalar, vec.z * scalar };
}

Vector2 Vec2ScalarAdd(Vector2 vec, float scalar)
{
	return (Vector2) { vec.x + scalar, vec.y + scalar };
}

Vector3 Vec3ScalarAdd(Vector3 vec, float scalar)
{
	return (Vector3) { vec.x + scalar, vec.y + scalar, vec.z + scalar };
}

Vector2 Vec2Multiply(Vector2 vec1, Vector2 vec2)
{
	return (Vector2) { vec1.x * vec2.x, vec1.y * vec2.y };
}

Vector3 Vec3Multiply(Vector3 vec1, Vector3 vec2)
{
	return (Vector3) { vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z };
}

Vector3 Vec3CrossProduct(Vector3 vec1, Vector3 vec2)
{
	return (Vector3) { (vec1.y * vec2.z) - (vec1.z * vec2.y), (vec1.z * vec2.x) - (vec1.x * vec2.z), (vec1.x * vec2.y) - (vec1.y * vec2.x) };
}

float Vec2DotProduct(Vector2 vec1, Vector2 vec2)
{
	return ((vec1.x * vec2.x) + (vec1.y * vec2.y));
}

float Vec3DotProduct(Vector3 vec1, Vector3 vec2)
{
	return ((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z));
}

Vector3 ForwardVec3(Vector3 vec3FromPos, Vector3 vec3ToPos) //Returns a Forward Vector
{
	Vector3 tmpVec = { 0, 0, 0 }; //Temporary vector for calculations
	Vector3 tmpVecReturn = { 0, 0, 0 }; //Temporary vector for calculations, returned

	tmpVec.x = vec3FromPos.x - vec3ToPos.x; //Calculates the X value of the Forward Vector
	tmpVec.y = vec3FromPos.y - vec3ToPos.y; //Calculates the Y value of the Forward Vector
	tmpVec.z = vec3FromPos.z - vec3ToPos.z; //Calculates the Z value of the Forward Vector

	tmpVecReturn = Vec3Normalize(tmpVec); //Calculates the normalized version of the forward vector

	return(tmpVecReturn);
}

Vector3 Vector3ZRotation(Vector3 inputVec3, float rotAmount) //Rotation of a 3D Vector around the Z-Axis (Roll)
{
	Vector3 tmpVecReturn = { 0, 0, 0 }; //Temporary vector for calculations, returned

	tmpVecReturn.x = (inputVec3.x * cos(rotAmount)) - (inputVec3.y * sin(rotAmount));
	tmpVecReturn.y = (inputVec3.x * sin(rotAmount)) - (inputVec3.y * cos(rotAmount));
	tmpVecReturn.z = inputVec3.z;

	return(tmpVecReturn);
}

Vector3 Vector3YRotation(Vector3 inputVec3, float rotAmount) //Rotation of a 3D Vector around the Y-Axis (Yaw)
{
	Vector3 tmpVecReturn = { 0, 0, 0 }; //Temporary vector for calculations, returned

	tmpVecReturn.x = (inputVec3.x * cos(rotAmount)) + (inputVec3.z * sin(rotAmount));
	tmpVecReturn.y = inputVec3.y;
	tmpVecReturn.z = (-inputVec3.x * sin(rotAmount)) + (inputVec3.z * cos(rotAmount));

	return(tmpVecReturn);
}

Vector3 Vector3XRotation(Vector3 inputVec3, float rotAmount) //Rotation of a 3D Vector around the X-Axis (Pitch)
{
	Vector3 tmpVecReturn = { 0, 0, 0 }; //Temporary vector for calculations, returned

	tmpVecReturn.x = inputVec3.x;
	tmpVecReturn.y = (inputVec3.y * cos(rotAmount)) - (inputVec3.z * sin(rotAmount));
	tmpVecReturn.z = (inputVec3.y * sin(rotAmount)) + (inputVec3.z * cos(rotAmount));

	return(tmpVecReturn);
}

Quaternion EulerToQuaternion(Vector3 eulerAngles) //Converts a set of Euler Angles to a Quaternion (Eruler == Yaw, Pitch, Roll)
{
	Quaternion tmpQuaternion = { 0, 0, 0, 0 }; //Temporary vector for Quaternion, returned

	float c1 = cos(eulerAngles.x / 2);
	float c2 = cos(eulerAngles.y / 2);
	float c3 = cos(eulerAngles.z / 2);
	float s1 = sin(eulerAngles.x / 2);
	float s2 = sin(eulerAngles.y / 2);
	float s3 = sin(eulerAngles.z / 2);

	tmpQuaternion.w = (c1 * c2 * c3) - (s1 * s2 * s3); //Conversion for the W-Variable of a Quaternion
	tmpQuaternion.x = (s1 * s2 * c3) + (c1 * c2 * s3); //Conversion for the X-Variable of a Quaternion
	tmpQuaternion.y = (s1 * c2 * c3) + (c1 * s2 * s3); //Conversion for the Y-Variable of a Quaternion
	tmpQuaternion.z = (c1 * s2 * c3) - (s1 * c2 * s3); //Conversion for the Z-Variable of a Quaternion
	
	return(tmpQuaternion);
}