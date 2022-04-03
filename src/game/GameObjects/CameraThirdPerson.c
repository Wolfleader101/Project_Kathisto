#include "CameraThirdPerson.h"

///////////////////////////////////////////
/////////	SETTING VARIABLES
///////////////////////////////////////////

//Setting the variables to default values

GameObjectManager gameManager; //Handles getting information from the Game Object Manager
GameObject * playerObject = NULL; //The object for the player

float camFocusRadius = 1.0f; //Relaxes the view of the focus point by a set amount

float camDistance = 3.0f; //The distance of the camera from the focal point
float camRotationSpeed = 90.0f; //The speed at which the camera rotates around the player object (In degrees per-second)
float camMinVertAngle = -10.0f; //The minimum value that the camera can rotate vertically
float camMaxVertAngle = 60.0f; //The maximum value that the camera can rotate vertically

Vector2 camOrbitAngles = {25.0f, 180.0f}; //Vertical (Pitch) angle, Horizontal (Yaw) angle

Vector3 camForwardDir; //The camera's forward direction (Vector)
Vector3 camPos = { 0.0f, 1.0f, 5.0f }; //The default camera position
Vector3 camUp; //The camera's Up-Vector

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

OnStart OnCamStart(GameObject* gameObject) //Sets the starting variables of the third person camera object
{
	gameObject->name = "player camera"; //Sets object name
	
	playerObject = GameObjectManagerFind(&gameManager, 2); //Sets the Player Object

	if (playerObject == NULL) //Check to make sure the Player Object has been set
	{
		return(1); //Returns an error if it hasn't been set
	}
}

OnUpdate OnCamUpdate(Time time, GameObject* gameObject) //Calculates the position aof the camera each frame
{
	//
	
	//LATE UPDATE SECTION

	Vector3 focusPoint = playerObject->transform.position; //The point that the camera is focusing on
	Vector3 lookAtDir = { camForwardDir.x, camForwardDir.y, camForwardDir.z }; //The direction (Forward vector), the camera is looking at

	camPos.x = focusPoint.x - lookAtDir.x * camDistance; //Calculates the camera's new x position
	camPos.y = focusPoint.y - lookAtDir.y * camDistance; //Calculates the camera's new y position
	camPos.z = focusPoint.z - lookAtDir.z * camDistance; //Calculates the camera's new z position

	//CAMERA POSITION CHANGE

	//Changes the position/rotation of the camera
	gluLookAt(	camPos.x, camPos.y, camPos.z,				//Camera X, Y, Z Position
				focusPoint.x, focusPoint.y, focusPoint.z,	//Camera X, Y, Z Focal Point
				camUp.x, camUp.y, camUp.z);					//Camera X, Y, Z Up-Vector
}

//////////////////////////////
////	REFERENCES
//////////////////////////////

// https://catlikecoding.com/unity/tutorials/movement/orbit-camera/
//		- Used for coding the camera rotation 