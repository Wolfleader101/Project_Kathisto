#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h" //Includes constant variables that are used across the game
#include "game/GameObjects/CameraThirdPerson.h" //Includes the third person camera

///////////////////////////////////////////
/////////	VARIABLES
///////////////////////////////////////////

extern float maxSpeed; //The maximum speed that the player can move at
extern float maxAcceleration; //The maximum acceleration that the player can achieve

extern Vector3 desiredPlayerVel; //The desired velocity of the player object

extern float rotSmoothSpeed; //The speed at which the player character will rotate

extern Vector2 playerInput; //The player movement inputs from the keyboard (Left/Right Movement, Forward/Back Movement)

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

/**
 * @brief The function which runs when the player object starts
 * @param GameObject* gameObject - Input game object
*/
OnStart OnPlayerStart(GameObject* gameObject); //Sets the starting variables of the player object

/**
 * @brief A function which is in charge of moving the player
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
*/
void MovePlayer(Time time, GameObject* gameObject); //Function to move the player relative to the camera object

/**
 * @brief A function which runs on each fixed update
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
*/
OnFixedUpdate OnPlayerFixedUpdate(Time time, GameObject* gameObject); //Updates every frame

/**
 * @brief Runs when a player collides into an object
 * @param Time time - The current game time
 * @param GameObject* gameObject - Input game object
 * @param GameObject* collisionObject - The object that the player is colliding with
*/
OnCollision OnPlayerCollision(Time time, GameObject* gameObject, GameObject* collisionObject);
