#include "CameraThirdPerson.h"

///////////////////////////////////////////
/////////	SETTING VARIABLES
///////////////////////////////////////////

//Setting the variables to default values

Vector3 cameraFocusPoint; //The point which the camera will focus on
float camFocusRadius = 1.0f; //Relaxes the view of the focus point by a set amount

float camDistance = 3.0f; //The distance of the camera from the focal point
float camRotationSpeed = 90.0f; //The speed at which the camera rotates around the player object (In degrees per-second)
float camMinVertAngle = -10.0f; //The minimum value that the camera can rotate vertically
float camMaxVertAngle = 60.0f; //The maximum value that the camera can rotate vertically

Vector2 camOrbitAngles = {25.0f, 180.0f}; //Vertical (Pitch) angle, Horizontal (Yaw) angle

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////