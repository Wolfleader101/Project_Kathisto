#include "Vector.h"

Vector2 EmptyVec2()
{
	return (Vector2){0.0f, 0.0f};
}

Vector3 EmptyVec3(){

	return (Vector3){0.0f, 0.0f, 0.0f};
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
