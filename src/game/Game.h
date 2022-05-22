#pragma once


#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"


void UpdateGameObjects(Time time, GameObjectManager* gameObjectManager);
void FixedUpdateGameObjects(Time fixedTime, GameObjectManager* gameObjectManager);

void InitGameObject(GameObject* gameObject); // initialise the game object
void SetupCallbacks(GameObject* gameObject, OnStart OnStart, OnUpdate OnUpdate, OnLateUpdate OnLateUpdate, OnFixedUpdate OnFixedUpdate); // setup the callbacks
void FreeGameObject(GameObject* gameObject); // free the game object

void InitTransform(Transform* transform);
void InitMesh(Mesh* mesh);
void InitRigidBody(RigidBody* RigidBody);

void UpdateGameObject(Time time, GameObject* gameObject); // called every frame update
void FixedUpdateGameObject(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject); // caled for physics update
void GravityTransform(Time fixedTime, GameObject* gameObject);

void UpdateTransform(Time time, Transform* transform);
void UpdateMesh(Time time, Mesh* mesh);
void DrawGizmos(Time time, Vector3 maxSize);
void DrawBoundingBox(BoudingBox box);

void CalculateBoundingBox(GameObject* gameObject);
void DetectCollision(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject);
