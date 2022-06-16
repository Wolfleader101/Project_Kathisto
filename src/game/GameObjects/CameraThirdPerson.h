#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameObjectManager.h"
#include "game/GameConstants.h"

#include "window/Events.h" //Includes Mouse Movements

///////////////////////////////////////////
/////////	VARIABLES
///////////////////////////////////////////

extern GameObject* playerObject; //The object for the player
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

extern Vector3 camForwardDirFlat; //The camera's default forward direction (Vector) flattened to have a Y of 0
Vector3 camRightFlat; //The camera's default right direction (Vector) flattened to have a Y of 0

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

/**
 * @brief Sets the initial attributes of the camera
 * @param GameObjectManager* gameObjectManager - Input Game Object Manager to find the player object
*/
void SetCamAttributes(GameObjectManager* gameObjectManager); //CALLED ONCE

/**
 * @brief Function to call all of the calculation functions
 * @param Time time - The current game time
*/
void ComputeCamPos(Time time); //LOOPED

/**
 * @brief Updates the focal point of the camera
*/
void UpdateCamFocus(); //LOOPED

/**
 * @brief The function which is in charge of rotating the camera
 * @param Time time - The current game time
*/
void ManualCamRotation(Time time); //LOOPED

/**
 * @brief Constrains the angles of the camera
*/
void ConstrainCamAngles(); //LOOPED

/**
 * @brief Calculates new position for the camera based on its movements
*/
void CalculateCamPosition(); //LOOPED

/**
 * @brief Calculates new vectors for the camera based on its movements
*/
void CalculateCamVectors(); //LOOPED

/**
 * @brief The function which is called to render the camera movements
 * @param Time time - The current game time
*/
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