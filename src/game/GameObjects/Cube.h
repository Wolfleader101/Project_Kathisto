#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"

#include "math/mathUtils.h"
#include "game/GameConstants.h"

/**
 * @brief The function which runs when the Cube object starts
 * @param GameObject* gameObject - Input game object
*/
OnStart OnCubeStart(GameObject* gameObject);

/**
 * @brief A function which runs on each update loop
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
*/
OnUpdate OnCubeUpdate(Time time, GameObject* gameObject);

/**
 * @brief A function which runs on each fixed update
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
*/
OnFixedUpdate OnCubeFixedUpdate(Time time, GameObject* gameObject);

/**
 * @brief Runs when a player collides into an object
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
 * @param GameObject* collisionObject - The object that the player is colliding with
*/
OnCollision OnCubeCollision(Time time, GameObject* gameObject, GameObject* collisionObject);