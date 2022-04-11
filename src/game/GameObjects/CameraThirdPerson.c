#include "CameraThirdPerson.h"

///////////////////////////////////////////
/////////	SETTING VARIABLES
///////////////////////////////////////////

//Setting the variables to default values

Vector3 tmpPosData = {0.0f, 1.0f, 0.0f}; //Temporary vector used to store data for passing between variables
Vector3 tmpRightData = {0.0f, 1.0f, 0.0f}; //Temporary arbitrary vector used to calculate the right vector

GameObject * playerObject = NULL; //The object for the player

Vector3 camFocusPoint = {0.0f, 0.0f, 0.0f}; //The point which the camera will focus on
float camFocusRadius = 1.0f; //Relaxes the view of the focus point by a set amount

float camDistance = 8.0f; //The distance of the camera from the focal point
float camRotationSpeed = 1.0f; //The speed at which the camera rotates around the player object (In degrees per-second)
float camMinVertAngle = -10.0f; //The minimum value that the camera can rotate vertically
float camMaxVertAngle = 60.0f; //The maximum value that the camera can rotate vertically

Vector3 camOrbitAngles = {25.0f, 180.0f, 0.0f}; //Vertical (Pitch) angle, Horizontal (Yaw) angle (EULER)

Vector3 camForwardDir = {0.0f, 0.0f, -1.0f}; //The camera's default forward direction (Vector)
Vector3 camPos = {0.0f, 4.0f, -3.5f}; //The default camera position
Vector3 camRight = { 1.0f, 0.0f, 0.0f }; //The camera's Right-Vector
Vector3 camUp = {0.0f, 1.0f, 0.0f}; //The camera's Up-Vector

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

void SetCamAttributes(GameObjectManager* gameObjectManager) //Sets the objects and variables used by the camera at the start - CALLED ONCE
{
	playerObject = GameObjectManagerFind(gameObjectManager, 2); //Sets the 'playerObject' to the Player in the Game Object Manager

	if(playerObject == NULL) //Checks to see if the object has been set
	{
		printf("ERROR: Player Object not found!");

		exit(1);
	}

	camFocusPoint = playerObject->transform.position; //The point that the camera is focusing on

	camForwardDir = ForwardVec3(camFocusPoint, camPos); //Initial calculation of the Forward Vector (Cross product of the focus point and camera position)
	camRight = Vec3CrossProduct(Vec3Normalize(tmpPosData), camForwardDir); //Calculate Right Vector (Using arbitrary vector and forward vector)
	camUp = Vec3CrossProduct(camForwardDir, camRight); //Calculate Up Vector (Cross product of the forward vector and right vector)
}

void ComputeCamPos(Time time) //Computes the camera position, rotation and such - LOOPED
{
	// UPDATE SECTION
	
	//

	//LATE UPDATE SECTION

	UpdateCamFocus();
	ManualCamRotation(time);

	CalculateCamPosition();
	CalculateCamVectors();
}

void CalculateCamPosition() //Calculates the cameras new position
{
	tmpPosData.y = camFocusPoint.y - camForwardDir.y * camDistance; //Calculates the camera's new y position (Y-Offset from Player)
	tmpPosData.x = camFocusPoint.x - camForwardDir.x * camDistance; //Calculates the camera's new x position (X-Offset from Player)
	tmpPosData.z = camFocusPoint.z - camForwardDir.z * camDistance; //Calculates the camera's new z position (Z-Offset from Player)

	camPos.x = tmpPosData.x; //Sets the variable camera position variable (used in gluLookAt), to the x position of camera object
	camPos.y = tmpPosData.y; //Sets the variable camera position variable (used in gluLookAt), to the y position of camera object
	camPos.z = tmpPosData.z; //Sets the variable camera position variable (used in gluLookAt), to the z position of camera object
}

void CalculateCamVectors() //Calculates the new vectors for the camera
{
	camForwardDir = ForwardVec3(camFocusPoint, camPos); //Initial calculation of the Forward Vector (Cross product of the focus point and camera position)
	camForwardDir = Vec3Normalize(camForwardDir);

	camRight.x = -(camForwardDir.z);
	camRight.y = 0.0f;
	camRight.z = camForwardDir.x;
	camRight = Vec3Normalize(camRight);

	camUp = Vec3CrossProduct(camForwardDir, camRight); //Calculate Up Vector (Cross product of the forward vector and right vector)
	camUp.y = -(camUp.y);
	camUp = Vec3Normalize(camUp);
}

void UpdateCamFocus() //Used to update the focus point of the camera each cycle
{
	Vector3 newFocusTarget = playerObject->transform.position; //The new position of the player that the camera will focus on

	camFocusPoint = newFocusTarget; //The focus point is set the the player's new position
}

void ManualCamRotation(Time time) //Calculates the camera's current rotation based on mouse inputs
{
	Vector2 currentMouseInputs = {mouseInputs.x, mouseInputs.y}; //The current inputs for the mouse

	const float e = 0.001f; //MOUSE SENSITIVITY - A check to make sure mouse inputs are above 0.001f

	if (currentMouseInputs.x < -(e) || currentMouseInputs.x > e)
	{
		if ((camOrbitAngles.y >= 360.0f) || ((camOrbitAngles.y < 0.0f)))
		{
			camOrbitAngles.y = 0.0f;
		}
		else
			camOrbitAngles.y += camRotationSpeed * time.currTime * mouseInputs.x;
	}
	
	if (currentMouseInputs.y < -(e) || currentMouseInputs.y > e)
	{
		if ((camOrbitAngles.x >= 90.0f) || ((camOrbitAngles.x < 0.0f)))
		{
			camOrbitAngles.x = 0.0f;
		}
		else
			camOrbitAngles.x += camRotationSpeed * time.currTime * mouseInputs.y;
	}
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