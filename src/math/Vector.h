#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Vector2
{
	float x;
	float y;
} Vector2;

typedef struct Vector3
{
	float x;
	float y;
	float z;
} Vector3;

typedef struct RGBA
{
	float r;
	float g;
	float b;
	float a;
} RGBA;

typedef struct Vector2Int
{
	int x;
	int y;
} Vector2Int;

typedef struct Vector3Int
{
	int x;
	int y;
	int z;
} Vector3Int;

typedef struct Quaternion
{
	float w;
	float x;
	float y;
	float z;
} Quaternion;

Vector2 EmptyVec2();
Vector3 EmptyVec3();
Quaternion EmptyQuaternion();

Vector2 ArrayToVec2(const float arr[2]);
Vector3 ArrayToVec3(const float arr[3]);
RGBA ArrayToRGBA(const float arr[4]);

float* Vec2ToArray(const Vector2 vec);
float* Vec3ToArray(const Vector3 vec);
float* RGBAToArray(const RGBA vec);
float* RGBAArrayToArray(const RGBA* vecArr, size_t length);

float Vec2Length(Vector2 vec);
float Vec3Length(Vector3 vec);

Vector2 Vec2Normalize(Vector2 vec);
Vector3 Vec3Normalize(Vector3 vec);

Vector2 Vec2ScalarMultiply(Vector2 vec, float scalar);
Vector3 Vec3ScalarMultiply(Vector3 vec, float scalar);

Vector2 Vec2ScalarAdd(Vector2 vec, float scalar);
Vector3 Vec3ScalarAdd(Vector3 vec, float scalar);

Vector2 Vec2Multiply(Vector2 vec1, Vector2 vec2);
Vector3 Vec3Multiply(Vector3 vec1, Vector3 vec2);

Vector2 Vec2Add(Vector2 vec1, Vector2 vec2);
Vector3 Vec3Add(Vector3 vec1, Vector3 vec2);

Vector2 Vec2Rotate(Vector2 vec, float angle);

Vector3 Vec3RotateX(Vector3 vec, float angle);
Vector3 Vec3RotateY(Vector3 vec, float angle);
Vector3 Vec3RotateZ(Vector3 vecz, float angle);

Vector3 Vec3CrossProduct(Vector3 vec1, Vector3 vec2);

float Vec2DotProduct(Vector2 vec1, Vector2 vec2);
float Vec3DotProduct(Vector3 vec1, Vector3 vec2);

Vector3 ForwardVec3(Vector3 vec3FromPos, Vector3 vec3ToPos); //Returns a Forward Vector

Vector3 Vector3ZRotation(Vector3 inputVec3, float rotAmount); //Rotation of a 3D Vector around the Z-Axis (Roll)
Vector3 Vector3YRotation(Vector3 inputVec3, float rotAmount); //Rotation of a 3D Vector around the Y-Axis (Yaw)
Vector3 Vector3XRotation(Vector3 inputVec3, float rotAmount); //Rotation of a 3D Vector around the X-Axis (Pitch)

Quaternion EulerToQuaternion(Vector3 eulerAngles); //Converts a set of Euler Angles to a Quaternion (Eruler == Yaw, Pitch, Roll)

//////////////////////////////
////	REFERENCES
//////////////////////////////

// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
//		- Used for calculating the forward vector
// https://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm
//		- Used for Euler to Quaternion conversion
// https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space
//		- 3D Vector Rotation