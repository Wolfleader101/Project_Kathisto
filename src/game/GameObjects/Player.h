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

extern Vector3 playerPos; //The position of the player

extern float maxSpeed; //The maximum speed that the player can move at
extern float maxAcceleration; //The maximum acceleration that the player can achieve

extern float maxAirAcceleration; //The maximum amount of control that the player has in the air
extern jumpHeight; //The maximum height that the player can jump

extern float rotSmoothSpeed; //The speed at which the player character will rotate

extern Vector3 playerMoveDir; 

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

OnStart OnPlayerStart(GameObject* gameObject); //Sets the starting variables of the player object

OnUpdate OnPlayerUpdate(GameObject* gameObject); //Updates every frame