#pragma once

#include <stdbool.h>
#include <math.h>

/**
 * @struct Vector2
 * @brief a vector2 structure
*/
typedef struct Vector2
{
	/**
	 * @brief X element of the Vector
	 */
	float x;
	/**
	 * @brief Y element of the Vector
	 */
	float y;
} Vector2;

/**
 * @struct Vector3
 * @brief a vector3 structure
*/
typedef struct Vector3
{
	/**
	 * @brief X element of the Vector
	 */
	float x;
	/**
	 * @brief Y element of the Vector
	 */
	float y;
	/**
	 * @brief Z element of the Vector
	 */
	float z;
} Vector3;

/**
 * @struct RGBA
 * @brief a rgba structure
*/
typedef struct RGBA
{
	/**
	 * @brief R element of the RGBA data
	 */
	float r;
	/**
	 * @brief G element of the RGBA data
	 */
	float g;
	/**
	 * @brief B element of the RGBA data
	 */
	float b;
	/**
	 * @brief A element of the RGBA data
	 */
	float a;
} RGBA;

/**
 * @struct Vector2Int
 * @brief a vector2 int structure
*/
typedef struct Vector2Int
{
	/**
	 * @brief X element of the Vector
	 */
	int x;
	/**
	 * @brief Y element of the Vector
	 */
	int y;
} Vector2Int;

/**
 * @struct Vector3Int
 * @brief a vector3 int structure
*/
typedef struct Vector3Int
{
	/**
	 * @brief X element of the Vector
	 */
	int x;
	/**
	 * @brief Y element of the Vector
	 */
	int y;
	/**
	 * @brief Z element of the Vector
	 */
	int z;
} Vector3Int;

/**
 * @struct Quaternion
 * @brief a quaternion structure
*/
typedef struct Quaternion
{
	/**
	 * @brief W element of the Vector
	 */
	float w;
	/**
	 * @brief X element of the Vector
	 */
	float x;
	/**
	 * @brief Y element of the Vector
	 */
	float y;
	/**
	 * @brief Z element of the Vector
	 */
	float z;
} Quaternion;

/**
 * @brief empty vector 2
 * @return empty vector 2
*/
Vector2 EmptyVec2();

/**
 * @brief empty vector 3
 * @return empty vector 3
*/
Vector3 EmptyVec3();

/**
 * @brief empty quaternion
 * @return empty quaternion
*/
Quaternion EmptyQuaternion();

/**
 * @brief if a vector2 is empty
 * @param vec to check
 * @return true if empty, else false
*/
bool isVec2Empty(Vector2 vec);
bool isVec3Empty(Vector3 vec);

/**
 * @brief array to a vector2
 * @param arr to convert
 * @return vector2 object
*/
Vector2 ArrayToVec2(const float arr[2]);

/**
 * @brief array to vector3
 * @param arr to convert
 * @return vector3 object
*/
Vector3 ArrayToVec3(const float arr[3]);

/**
 * @brief array to rgba
 * @param arr to convert
 * @return rgba object
*/
RGBA ArrayToRGBA(const float arr[4]);

/**
 * @brief vec2 to float array
 * @param vec to convert
 * @return float array
*/
float* Vec2ToArray(const Vector2 vec);

/**
 * @brief vec3 to float array
 * @param vec to convert
 * @return float array
*/
float* Vec3ToArray(const Vector3 vec);

/**
 * @brief rgba to float array
 * @param vec to convert
 * @return float array
*/
float* RGBAToArray(const RGBA vec);

/**
 * @brief convert rgba array to float array
 * @param vecArr to convert
 * @param length of array
 * @return float array
*/
float* RGBAArrayToArray(const RGBA* vecArr, size_t length);

/**
 * @brief get the magnitude of a vector 2
 * @param vec to get magnitude from
 * @return magnitude of vector
*/
float Vec2Length(Vector2 vec);

/**
 * @brief get the magnitude of a vector 3
 * @param vec to get magnitude from
 * @return magnitude of vector
*/
float Vec3Length(Vector3 vec);

/**
 * @brief normalise a vector2
 * @param vec to normalize
 * @return normalized vector2
*/
Vector2 Vec2Normalize(Vector2 vec);

/**
 * @brief normalize a vector3
 * @param vec to normalize
 * @return normalized vector3
*/
Vector3 Vec3Normalize(Vector3 vec);

/**
 * @brief scalar multiply a vector2
 * @param vec to multply
 * @param scalar to muliply
 * @return vector2 scalar multplied
*/
Vector2 Vec2ScalarMultiply(Vector2 vec, float scalar);

/**
 * @brief scalar multiply a vector3
 * @param vec to multply
 * @param scalar to muliply
 * @return vector3 scalar multplied
*/
Vector3 Vec3ScalarMultiply(Vector3 vec, float scalar);

/**
 * @brief scalar add a vector2
 * @param vec to add
 * @param scalar to add
 * @return vector2 scalar added
*/
Vector2 Vec2ScalarAdd(Vector2 vec, float scalar);

/**
 * @brief scalar add a vector3
 * @param vec to add
 * @param scalar to add
 * @return vector3 scalar added
*/
Vector3 Vec3ScalarAdd(Vector3 vec, float scalar);

/**
 * @brief scalar add a vector2
 * @param vec to subtract
 * @param scalar to subtract
 * @return vector2 scalar subtracted
*/
Vector2 Vec2ScalarSubtract(Vector2 vec, float scalar);

/**
 * @brief scalar add a vector3
 * @param vec to subtract
 * @param scalar to subtract
 * @return vector3 scalar subtracted
*/
Vector3 Vec3ScalarSubtract(Vector3 vec, float scalar);

/**
 * @brief multiply 2 vectors2
 * @param vec1 to multiply
 * @param vec2 to multiply
 * @return the multiplied vector2
*/
Vector2 Vec2Multiply(Vector2 vec1, Vector2 vec2);

/**
 * @brief multiply 2 vectors3
 * @param vec1 to multiply
 * @param vec2 to multiply
 * @return the multiplied vector3
*/
Vector3 Vec3Multiply(Vector3 vec1, Vector3 vec2);

/**
 * @brief add 2 vectors2
 * @param vec1 to add
 * @param vec2 to add
 * @return the add vector2
*/
Vector2 Vec2Add(Vector2 vec1, Vector2 vec2);

/**
 * @brief add 2 vectors3
 * @param vec1 to add
 * @param vec2 to add
 * @return the addeded vector3
*/
Vector3 Vec3Add(Vector3 vec1, Vector3 vec2);

/**
 * @brief subtract 2 vectors2
 * @param vec1 to subtract
 * @param vec2 to subtract
 * @return the subtracted vector2
*/
Vector2 Vec2Subtract(Vector2 vec1, Vector2 vec2);

/**
 * @brief subtract 2 vectors3
 * @param vec1 to subtract
 * @param vec2 to subtract
 * @return the subtracted vector3
*/
Vector3 Vec3Subtract(Vector3 vec1, Vector3 vec2);

/**
 * @brief rotate a vector2
 * @param vec to rotate
 * @param angle in radians to rotate
 * @return rotated vector
*/
Vector2 Vec2Rotate(Vector2 vec, float angle);

/**
 * @brief rotate a vector3 around X
 * @param vec to rotate
 * @param angle in radians to rotate around
 * @return a rotated vector3
*/
Vector3 Vec3RotateX(Vector3 vec, float angle);

/**
 * @brief rotate a vector3 around Y
 * @param vec to rotate
 * @param angle in radians to rotate around
 * @return a rotated vector3
*/
Vector3 Vec3RotateY(Vector3 vec, float angle);

/**
 * @brief rotate a vector3 around Z
 * @param vec to rotate
 * @param angle in radians to rotate around
 * @return a rotated vector3
*/
Vector3 Vec3RotateZ(Vector3 vec, float angle);

/**
 * @brief cross product 2 vector3's
 * @param vec1 to cross
 * @param vec2 to cross
 * @return the cross product of vec1 and vec2
*/
Vector3 Vec3CrossProduct(Vector3 vec1, Vector3 vec2);

/**
 * @brief dot product 2 vector2s
 * @param vec1 to dot product
 * @param vec2 to dot product
 * @return the dot product of vec1 and vec2
*/
float Vec2DotProduct(Vector2 vec1, Vector2 vec2);

/**
 * @brief dot product 2 vector3s
 * @param vec1 to dot product
 * @param vec2 to dot product
 * @return the dot product of vec1 and vec2
*/
float Vec3DotProduct(Vector3 vec1, Vector3 vec2);

/**
 * @brief converts a set of Euler Angles to a Quaternion
 * @param eulerAngles to convert, Yaw, Pitch, Roll
 * @return quaternion
*/
Quaternion EulerToQuaternion(Vector3 eulerAngles);

//////////////////////////////
////	REFERENCES
//////////////////////////////

// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
//		- Used for calculating the forward vector
// https://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm
//		- Used for Euler to Quaternion conversion