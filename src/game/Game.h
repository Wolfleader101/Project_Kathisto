#pragma once


#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"
#include "game/Physics.h"
#include "game/Rendering.h"


void InitGameObject(GameObject* gameObject); // initialise the game object
void InitTransform(Transform* transform);

void SetupCallbacks(GameObject* gameObject, OnStart OnStart, OnUpdate OnUpdate, OnLateUpdate OnLateUpdate, OnFixedUpdate OnFixedUpdate, OnCollision OnCollision); // setup the callbacks
void FreeGameObject(GameObject* gameObject); // free the game object

void UpdateGameObjects(Time time, GameObjectManager* gameObjectManager);

void UpdateGameObject(Time time, GameObject* gameObject); // called every frame update

void UpdateTransform(Time time, Transform* transform);
