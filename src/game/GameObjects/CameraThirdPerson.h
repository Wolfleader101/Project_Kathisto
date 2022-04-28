#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "math/Vector.h" //Includes definitions for Vectors
#include "game/GameConstants.h" //Includes constant variables that are used across the game
#include "math/mathUtils.h" //Includes custom maths utilities

#include "game/Game.h" //Includes the Game Object struct so I can access the player object

#include "window/Events.h" //Includes Mouse Movements

///////////////////////////////////////////
/////////	VARIABLES
///////////////////////////////////////////

extern Vector3 tmpPosData; //Temporary vector used to store data for passing between variables
extern Vector3 tmpRightData; //Temporary arbitrary vector used to calculate the right vector

extern GameObject * playerObject; //The object for the player

extern Vector3 camFocusPoint; //The point which the camera will focus on
extern float camFocusRadius; //Relaxes the view of the focus point by a set amount

extern float camDistance; //The distance of the camera from the focal point
extern float camRotationSpeed; //The speed at which the camera rotates around the player object (In degrees per-second)
extern float camMinVertAngle; //The minimum value that the camera can rotate vertically
extern float camMaxVertAngle; //The maximum value that the camera can rotate vertically

extern Vector3 camOrbitAngles; //Vertical (Pitch) angle, Horizontal (Yaw) angle (EULER)

extern Vector3 camForwardDir; //The camera's forward direction (Vector)
extern Vector3 camPos; //The camera's position
extern Vector3 camRight; //The camera's Right-Vector
extern Vector3 camUp; //The camera's Up-Vector

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

void SetCamAttributes(GameObjectManager* gameObjectManager); //CALLED ONCE

void ComputeCamPos(Time time); //LOOPED

void UpdateCamFocus(); //LOOPED

void ManualCamRotation(Time time); //LOOPED

void ConstrainCamAngles(); //LOOPED

void CalculateCamPosition(); //LOOPED

void CalculateCamVectors(); //LOOPED

void ThirdPersonCamRender(Time time); //LOOPED

//////////////////////////////
////	REFERENCES
//////////////////////////////

// https://catlikecoding.com/unity/tutorials/movement/orbit-camera/
//		- Used for coding the camera rotation 
// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
//		- Used for calculating the forward vector and cross product
// https://stackoverflow.com/questions/38751103/orbit-camera-c-glm
//		- Used for Camera Rotations around a point
// https://technotip.com/7376/c-program-to-convert-degree-to-radian/
//		- Converting from Degrees to Radians
// https://www.braynzarsoft.net/viewtutorial/q16390-32-simple-3rd-person-camera
//		- Calculating Forward, Right and Up Vectors