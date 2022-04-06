#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <GL/freeglut.h>

#include "math/Vector.h"

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
} Mesh;

typedef struct RigidBody
{
	bool isStatic;
	bool useGravity;
	float mass;
	float velocity;

	BoudingBox boundingBox;

} RigidBody;

typedef struct BoudingBox
{
	Vector3 minPos;
	Vector3 maxPos;
	size_t gameObjectId;
} BoudingBox;

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


typedef struct GameObjectManager
{
	GameObject** gameObjects;
	BoudingBox** boundingBoxes;

	size_t count;
	size_t lastIndex;
	size_t freeSpace;
} GameObjectManager;


// game manager struct??
// contains all managers, e.g game object manager etc
// not needed for this unit tbh

void InitGameObjectManager(GameObjectManager* gameObjectManager);
void GameObjectManagerIncrease(GameObjectManager* gameObjectManager);
void GameObjectManagerAdd(GameObjectManager* gameObjectManager, GameObject* GameObject);
void GameObjectManagerRemove(GameObjectManager* gameObjectManager, size_t id);
GameObject* GameObjectManagerFind(GameObjectManager* gameObjectManager, size_t id);
void UpdateGameObjects(Time time, GameObjectManager* gameObjectManager);
void FixedUpdateGameObjects(Time time, GameObjectManager* gameObjectManager);

void InitGameObject(GameObject* gameObject); // initialise the game object
void SetupCallbacks(GameObject* gameObject, OnStart OnStart, OnUpdate OnUpdate, OnLateUpdate OnLateUpdate, OnFixedUpdate OnFixedUpdate); // setup the callbacks
void FreeGameObject(GameObject* gameObject); // free the game object

void InitTransform(Transform* transform);
void InitMesh(Mesh* mesh);
void InitRigidBody(RigidBody* RigidBody);

void UpdateGameObject(Time time, GameObject* gameObject); // called every frame update
void FixedUpdateGameObject(Time time, GameObject* gameObject); // caled for physics update

void UpdateTransform(Time time, Transform* transform);
void UpdateMesh(Time time, Mesh* mesh);
void DrawGizmos(Time time, Vector3 maxSize);

void CalculateBoundingBox(GameObject* gameObject);
void DetectCollision(GameObjectManager* gameObjectManager, GameObject* gameObject);

void SimulateRigidBody(RigidBody* RigidBody); // simulate rigid body
