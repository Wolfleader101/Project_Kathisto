#include "CameraThirdPerson.h"

///////////////////////////////////////////
/////////	SETTING VARIABLES
///////////////////////////////////////////

//Setting the variables to default values

float camFocusRadius = 1.0f; //Relaxes the view of the focus point by a set amount

float camDistance = 3.0f; //The distance of the camera from the focal point
float camRotationSpeed = 90.0f; //The speed at which the camera rotates around the player object (In degrees per-second)
float camMinVertAngle = -10.0f; //The minimum value that the camera can rotate vertically
float camMaxVertAngle = 60.0f; //The maximum value that the camera can rotate vertically

Vector2 camOrbitAngles = {25.0f, 180.0f}; //Vertical (Pitch) angle, Horizontal (Yaw) angle

Vector3 camPos = {0.0f, 1.0f, 5.0f}; //The default camera position

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

OnUpdate OnCameraUpdate(Time time, GameObject* gameObject)
{
	//
	
	//LATE UPDATE SECTION

	Vector3 focusPoint; //The point that the camera is focusing on
	Vector3 lookAtDir; //The direction (Forward vector), the camera is looking at

	//camPos = focusPoint - lookAtDir * camDistance; //Calculates the camera's new position
}