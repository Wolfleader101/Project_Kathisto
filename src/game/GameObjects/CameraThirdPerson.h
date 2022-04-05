#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "math/Vector.h" //Includes definitions for Vectors
#include "game/GameConstants.h" //Includes constant variables that are used across the game

#include "game/Game.h" //Includes the Game Object struct so I can access the player object

#include <window/Window.h> //Gives me access to the Game Manager used for the project

///////////////////////////////////////////
/////////	VARIABLES
///////////////////////////////////////////

extern GameObject * playerObject; //The object for the player
extern GameObject * camObject; //The object for the third person camera

extern Vector3 camFocusPoint; //The point which the camera will focus on
extern float camFocusRadius; //Relaxes the view of the focus point by a set amount

extern float camDistance; //The distance of the camera from the focal point
extern float camRotationSpeed; //The speed at which the camera rotates around the player object (In degrees per-second)
extern float camMinVertAngle; //The minimum value that the camera can rotate vertically
extern float camMaxVertAngle; //The maximum value that the camera can rotate vertically

extern Vector2 camOrbitAngles; //Vertical (Pitch) angle, Horizontal (Yaw) angle

extern Vector3 camForwardDir; //The camera's forward direction (Vector)
extern Vector3 camPos; //The camera's position
extern Vector3 camUp; //The camera's Up-Vector

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

void ComputeCamPos(float deltaTime);

void ThirdPersonCamRender(float deltaTime);