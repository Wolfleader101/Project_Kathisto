#pragma once

#include "GameIncludes.h"

typedef struct Time
{
	float currTime;
	float prevTime;
	float deltaTime;
} Time;

typedef struct Transform
{
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

} Transform;

typedef struct Mesh
{
	Vector3* points;
	size_t pointSize;
	Vector3Int* indices;
	int indexCount;
	RGBA* colors;
	bool isUniformColor;
	bool debug;
	bool disableMesh;
} Mesh;

typedef struct BoudingBox
{
	Vector3 minPos;
	Vector3 maxPos;
	size_t gameObjectId;
} BoudingBox;

typedef struct SphereBody
{
	bool isSphere;
	float radius;

} SphereBody;

typedef struct RigidBody
{
	bool isStatic;
	bool isFloor;
	bool onGround;
	bool useGravity;
	float mass;
	Vector3 velocity;

	SphereBody sphereBody;
	BoudingBox boundingBox;

	bool debug;
} RigidBody;

typedef struct GameObject GameObject;
typedef void (*OnStart)(GameObject*);
typedef void (*OnUpdate)(Time, GameObject*);
typedef void (*OnLateUpdate)(Time, GameObject*);
typedef void (*OnFixedUpdate)(Time, GameObject*);

struct GameObject
{
	size_t id;
	char* name;
	Transform transform;
	Mesh mesh;
	RigidBody rigidBody;
	bool debug;

	OnStart OnStart;
	OnUpdate OnUpdate;
	OnLateUpdate OnLateUpdate;
	OnFixedUpdate OnFixedUpdate;
};

/**
 * @brief GameObjectManager struct which contains an array of gameobject pointers, and bounding boxes
*/
typedef struct GameObjectManager
{
	GameObject** gameObjects;
	BoudingBox** boundingBoxes;

	size_t count;
	size_t lastIndex;
	size_t freeSpace;
} GameObjectManager;

typedef enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FORWARD,
	BACK,
} CollisionDir;

typedef struct CollisionData
{
	GameObject* collidingGameObject;
	CollisionDir collidingFace;
} CollisionData;