#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h" //Includes definitions for Vectors
#include "game/Game.h" //Includes defintions for Start and Update functions
#include "game/GameConstants.h" //Includes constant variables that are used across the game
#include "game/GameObjects/CameraThirdPerson.h" //Includes the third person camera

///////////////////////////////////////////
/////////	VARIABLES
///////////////////////////////////////////

extern float maxSpeed; //The maximum speed that the player can move at
extern float maxAcceleration; //The maximum acceleration that the player can achieve

extern Vector3 desiredPlayerVel; //The desired velocity of the player object
extern Vector3 playerVel; //The current velocity of the player object

extern float rotSmoothSpeed; //The speed at which the player character will rotate

extern Vector2 playerInput; //The player movement inputs from the keyboard (Left/Right Movement, Forward/Back Movement)

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

OnStart OnPlayerStart(GameObject* gameObject); //Sets the starting variables of the player object

void CalculatePlayerVelcoity(Time time); //Calculates the velocity of the player each frame

OnUpdate OnPlayerUpdate(Time time, GameObject* gameObject); //Updates every frame