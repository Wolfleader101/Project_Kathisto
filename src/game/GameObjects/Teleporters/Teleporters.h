#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameObjectManager.h"

extern const RGBA Teleporter1ColorBuffer[1];
extern const RGBA Teleporter2ColorBuffer[1];

extern bool areTeleportersReady;
extern const float maxTeleCooldown;
extern float teleCooldown;

/**
 * @brief The function which runs when the Teleporter 1 object starts
 * @param GameObject* gameObject - Input game object
*/
OnStart OnTeleporter1Start(GameObject* gameObject);
/**
 * @brief The function which runs when the Teleporter 2 object starts
 * @param GameObject* gameObject - Input game object
*/
OnStart OnTeleporter2Start(GameObject* gameObject);

/**
 * @brief Runs when an object collides into the teleporter
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
 * @param GameObject* collisionObject - The object that the player is colliding with
*/
OnCollision OnTeleporter1Collision(Time time, GameObject* gameObject, GameObject* collisionObject);
/**
 * @brief Runs when an object collides into the teleporter
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
 * @param GameObject* collisionObject - The object that the player is colliding with
*/
OnCollision OnTeleporter2Collision(Time time, GameObject* gameObject, GameObject* collisionObject);

/**
 * @brief A function which runs on each update loop
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
*/
OnUpdate OnTeleporter1Update(Time time, GameObject* gameObject);