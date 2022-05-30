#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/Game.h"

/**
 * @brief initialise a game object with default values
 * @param gameObject to intialise
*/
void InitGameObject(GameObject* gameObject);

/**
 * @brief initialise the transform component of a gameobject
 * @param transform to initialise
*/
void InitTransform(Transform* transform);

/**
 * @brief setup the callbacks on a gameObject
 * @param gameObject to add callbacks too
 * @param OnStart callback to add
 * @param OnUpdate callback to add
 * @param OnLateUpdate callback to add
 * @param OnFixedUpdate callback to add
*/
void SetupCallbacks(GameObject* gameObject, OnStart OnStart, OnUpdate OnUpdate, OnLateUpdate OnLateUpdate, OnFixedUpdate OnFixedUpdate);

/**
 * @brief free the game object
 * @param gameObject to free
*/
void FreeGameObject(GameObject* gameObject);

/**
 * @brief called every frame which updates a gameobject
 * @param time to update smoothly
 * @param gameObject to update
*/
void UpdateGameObject(Time time, GameObject* gameObject);

/**
 * @brief update the transform of a gameobject
 * @param time to update smoothly
 * @param transform component to update
*/
void UpdateTransform(Time time, Transform* transform);
