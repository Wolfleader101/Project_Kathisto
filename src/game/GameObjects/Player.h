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

OnStart OnPlayerStart(GameObject* gameObject); //Sets the starting variables of the player object

void MovePlayer(Time time, GameObject* gameObject); //Function to move the player relative to the camera object

OnFixedUpdate OnPlayerFixedUpdate(Time time, GameObject* gameObject); //Updates every frame

OnCollision OnPlayerCollision(Time time, GameObject* gameObject, GameObject* collisionObject);
