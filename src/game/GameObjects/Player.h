#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h" //Includes definitions for Vectors
#include "game/Game.h" //Includes defintions for Start and Update functions
#include "game/GameConstants.h" //Includes constant variables that are used across the game

///////////////////////////////////////////
/////////	VARIABLES
///////////////////////////////////////////

Vector3 playerPos; //The position of the player

float maxSpeed; //The maximum speed that the player can move at
float maxAcceleration; //The maximum acceleration that the player can achieve

float maxAirAcceleration; //The maximum amount of control that the player has in the air
float jumpHeight; //The maximum height that the player can jump

float rotSmoothSpeed; //The speed at which the player character will rotate

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

OnStart OnPlayerStart(GameObject* gameObject); //Sets the starting variables of the player object