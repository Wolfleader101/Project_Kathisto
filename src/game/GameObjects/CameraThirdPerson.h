#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "math/Vector.h" //Includes definitions for Vectors
#include "game/GameConstants.h" //Includes constant variables that are used across the game

#include "Player.h" //Includes the player object

///////////////////////////////////////////
/////////	VARIABLES
///////////////////////////////////////////

extern Vector3 cameraFocusPoint; //The point which the camera will focus on
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

OnUpdate OnCameraUpdate(Time time, GameObject* gameObject);