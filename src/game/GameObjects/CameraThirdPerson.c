#include "CameraThirdPerson.h"

///////////////////////////////////////////
/////////	SETTING VARIABLES
///////////////////////////////////////////

//Setting the variables to default values

GameObject * playerObject = NULL; //The object for the player
GameObject * camObject = NULL; //The object for the third person camera

Vector3 camFocusPoint; //The point which the camera will focus on
float camFocusRadius = 1.0f; //Relaxes the view of the focus point by a set amount

float camDistance = 3.0f; //The distance of the camera from the focal point
float camRotationSpeed = 90.0f; //The speed at which the camera rotates around the player object (In degrees per-second)
float camMinVertAngle = -10.0f; //The minimum value that the camera can rotate vertically
float camMaxVertAngle = 60.0f; //The maximum value that the camera can rotate vertically

Vector2 camOrbitAngles = {25.0f, 180.0f}; //Vertical (Pitch) angle, Horizontal (Yaw) angle

Vector3 camForwardDir = { 0.0f, 0.0f, -1.0f }; //The camera's default forward direction (Vector)
Vector3 camPos = { 0.0f, 1.0f, 5.0f }; //The default camera position
Vector3 camUp; //The camera's Up-Vector

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

void ComputeCamPos(float deltaTime)
{
	playerObject = GameObjectManagerFind(&gameObjectManager, 1);

	printf("%s\n", playerObject->name);
	
	//

	//LATE UPDATE SECTION

	Vector3 tmpPosData;

	camFocusPoint = playerObject->transform.position; //The point that the camera is focusing on

	tmpPosData.x = camFocusPoint.x - camForwardDir.x * camDistance; //Calculates the camera's new x position
	tmpPosData.y = camFocusPoint.y - camForwardDir.y * camDistance; //Calculates the camera's new y position
	tmpPosData.z = camFocusPoint.z - camForwardDir.z * camDistance; //Calculates the camera's new z position

	camPos.x = tmpPosData.x; //Sets the variable camera position variable (used in gluLookAt), to the x position of camera object
	camPos.y = tmpPosData.y; //Sets the variable camera position variable (used in gluLookAt), to the y position of camera object
	camPos.z = tmpPosData.z; //Sets the variable camera position variable (used in gluLookAt), to the z position of camera object
}

void ThirdPersonCamRender(float deltaTime)
{
	// compute the cameras position you can move
	ComputeCamPos(deltaTime);

	//CAMERA POSITION CHANGE

	//Changes the position/rotation of the camera
	gluLookAt(camPos.x, camPos.y, camPos.z,					//Camera X, Y, Z Position
		camFocusPoint.x, camFocusPoint.y, camFocusPoint.z,			//Camera X, Y, Z Focal Point
		camUp.x, camUp.y, camUp.z);							//Camera X, Y, Z Up-Vector
}

//////////////////////////////
////	REFERENCES
//////////////////////////////

// https://catlikecoding.com/unity/tutorials/movement/orbit-camera/
//		- Used for coding the camera rotation 