#include "CameraThirdPerson.h"

///////////////////////////////////////////
/////////	SETTING VARIABLES
///////////////////////////////////////////

//Setting the variables to default values

Vector3 tmpPosData = { 0.0f, 0.0f, 0.0f }; //Temporary vector used to store data for passing between variables

GameObject * playerObject = NULL; //The object for the player

Vector3 camFocusPoint = { 0.0f, 0.0f, 0.0f }; //The point which the camera will focus on
float camFocusRadius = 1.0f; //Relaxes the view of the focus point by a set amount

float camDistance = 3.0f; //The distance of the camera from the focal point
float camRotationSpeed = 90.0f; //The speed at which the camera rotates around the player object (In degrees per-second)
float camMinVertAngle = -10.0f; //The minimum value that the camera can rotate vertically
float camMaxVertAngle = 60.0f; //The maximum value that the camera can rotate vertically

Vector2 camOrbitAngles = {25.0f, 180.0f}; //Vertical (Pitch) angle, Horizontal (Yaw) angle

Vector3 camForwardDir = { 0.0f, 0.0f, -1.0f }; //The camera's default forward direction (Vector)
Vector3 camPos = { 0.0f, 1.0f, 5.0f }; //The default camera position
Vector3 camUp = { 0.0f, 1.0f, 0.0f }; //The camera's Up-Vector

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

void SetCamObjects(GameObjectManager* gameObjectManager) //Sets the objects used by the camera - CALLED ONCE
{
	playerObject = GameObjectManagerFind(&*gameObjectManager, 2); //Sets the 'playerObject' to the Player in the Game Object Manager

	if(playerObject == NULL) //Checks to see if the object has been set
	{
		printf("ERROR: Player Object not found!");

		exit(1);
	}

	printf(&playerObject->name);
}

void ComputeCamPos(Time time) //Computes the camera position, rotation and such - LOOPED
{
	// UPDATE SECTION
	
	//

	//LATE UPDATE SECTION

	camFocusPoint = playerObject->transform.position; //The point that the camera is focusing on

	tmpPosData.x = camFocusPoint.x - camForwardDir.x * camDistance; //Calculates the camera's new x position
	tmpPosData.y = camFocusPoint.y - camForwardDir.y * camDistance; //Calculates the camera's new y position
	tmpPosData.z = camFocusPoint.z - camForwardDir.z * camDistance; //Calculates the camera's new z position

	camPos.x = tmpPosData.x; //Sets the variable camera position variable (used in gluLookAt), to the x position of camera object
	camPos.y = tmpPosData.y; //Sets the variable camera position variable (used in gluLookAt), to the y position of camera object
	camPos.z = tmpPosData.z; //Sets the variable camera position variable (used in gluLookAt), to the z position of camera object
}

void ThirdPersonCamRender(Time time) //Computes the camera position, rotation and such - LOOPED
{
	//Computes the camera's new position, look at position and rotation around the player
	ComputeCamPos(time);

	//CAMERA POSITION CHANGE

	//Changes the position/rotation of the camera
	gluLookAt(camPos.x, camPos.y, camPos.z,					//Camera X, Y, Z Position
		camFocusPoint.x, camFocusPoint.y, camFocusPoint.z,	//Camera X, Y, Z Focal Point
		camUp.x, camUp.y, camUp.z);							//Camera X, Y, Z Up-Vector
}

//////////////////////////////
////	REFERENCES
//////////////////////////////

// https://catlikecoding.com/unity/tutorials/movement/orbit-camera/
//		- Used for coding the camera rotation 