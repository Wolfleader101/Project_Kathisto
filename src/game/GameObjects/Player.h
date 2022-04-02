#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h" //Includes definitions for Vectors
#include "game/Game.h" //Includes defintions for Start and Update functions
#include "game/GameConstants.h" //Includes constant variables that are used across the game

OnStart OnPlayerStart(GameObject* gameObject); //Sets the starting variables of the player object