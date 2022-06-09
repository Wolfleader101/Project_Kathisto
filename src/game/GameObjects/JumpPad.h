#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"

#include "math/mathUtils.h"
#include "game/GameConstants.h"


//isReady performs 'cooldown' for jump pad applying the jump boost
extern bool isReady;
extern float cooldown;
extern GameObject* collidingObject;

extern const RGBA JumpPadColorBuffer[1];

/**
 * @brief The function which runs when the Jump Pad object starts
 * @param GameObject* gameObject - Input game object
*/
OnStart OnJumpPadStart(GameObject* gameObject);

/**
 * @brief A function which runs on each update loop
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
*/
OnUpdate OnJumpPadUpdate(Time time, GameObject* gameObject);

/**
 * @brief A function which runs on each fixed update
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
*/
OnFixedUpdate OnJumpPadFixedUpdate(Time time, GameObject* gameObject);

/**
 * @brief Runs when a player collides into an object
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
 * @param GameObject* collisionObject - The object that the player is colliding with
*/
OnCollision OnJumpPadCollision(Time time, GameObject* gameObject, GameObject* collisionObject);