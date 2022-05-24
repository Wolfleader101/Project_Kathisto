#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/Game.h"


void InitGameObject(GameObject* gameObject); // initialise the game object
void InitTransform(Transform* transform);

void SetupCallbacks(GameObject* gameObject, OnStart OnStart, OnUpdate OnUpdate, OnLateUpdate OnLateUpdate, OnFixedUpdate OnFixedUpdate); // setup the callbacks
void FreeGameObject(GameObject* gameObject); // free the game object

void UpdateGameObject(Time time, GameObject* gameObject); // called every frame update
void UpdateTransform(Time time, Transform* transform);