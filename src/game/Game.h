#pragma once


#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"
#include "game/Physics.h"


void UpdateGameObjects(Time time, GameObjectManager* gameObjectManager);

void InitGameObject(GameObject* gameObject); // initialise the game object
void SetupCallbacks(GameObject* gameObject, OnStart OnStart, OnUpdate OnUpdate, OnLateUpdate OnLateUpdate, OnFixedUpdate OnFixedUpdate); // setup the callbacks
void FreeGameObject(GameObject* gameObject); // free the game object

void InitTransform(Transform* transform);
void InitMesh(Mesh* mesh);

void UpdateGameObject(Time time, GameObject* gameObject); // called every frame update

void UpdateTransform(Time time, Transform* transform);
void UpdateMesh(Time time, Mesh* mesh);
void DrawGizmos(Time time, Vector3 maxSize);
void DrawBoundingBox(BoudingBox box);