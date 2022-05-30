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
float camRotationSpeed = 15.0f; //The speed at which the camera rotates around the player object (In degrees per-second)
float camMinVertAngle = -4.0f; //The minimum value that the camera can rotate vertically
float camMaxVertAngle = 50.0f; //The maximum value that the camera can rotate vertically

Vector3 camOrbitAngles = {0.0f, 360.0f, 0.0f}; //Vertical (Pitch) angle, Horizontal (Yaw) angle (EULER)

Vector3 camForwardDir = {0.0f, 0.0f, -1.0f}; //The camera's default forward direction (Vector)
Vector3 camPos = {0.0f, 4.0f, -3.5f}; //The default camera position
Vector3 camRight = { 1.0f, 0.0f, 0.0f }; //The camera's Right-Vector
Vector3 camUp = {0.0f, 1.0f, 0.0f}; //The camera's Up-Vector

Vector3 camForwardDirFlat = { 0.0f, 0.0f, -1.0f }; //The camera's default forward direction (Vector) flattened to have a Y of 0
Vector3 camRightFlat = { 1.0f, 0.0f, 0.0f }; //The camera's default right direction (Vector) flattened to have a Y of 0

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

	CalculateCamVectors(); //Initially calculates the vectors for the camera
}

void ComputeCamPos(Time time) //Computes the camera position, rotation and such - LOOPED
{
	// UPDATE SECTION
	
	//

	//LATE UPDATE SECTION

	UpdateCamFocus();

	CalculateCamVectors();

	ManualCamRotation(time);

	CalculateCamPosition();
}

void UpdateCamFocus() //Used to update the focus point of the camera each cycle
{
	Vector3 newFocusTarget = playerObject->transform.position; //The new position of the player that the camera will focus on

	camFocusPoint = newFocusTarget; //The focus point is set the the player's new position
}

void ManualCamRotation(Time time) //Calculates the camera's current rotation based on mouse inputs
{
	camOrbitAngles.x += camRotationSpeed * time.currTime * mouseInputs.y; //Calculates the x orbit angle (Pitch)
	camOrbitAngles.y += camRotationSpeed * time.currTime * mouseInputs.x; //Calculates the y orbit angle (Yaw)

	ConstrainCamAngles();

	camForwardDir.x = cos((camOrbitAngles.y / 180) * PI_CONST) * cos((camOrbitAngles.x / 180) * PI_CONST);
	camForwardDir.y = -sin((camOrbitAngles.x / 180) * PI_CONST);
	camForwardDir.z = sin((camOrbitAngles.y / 180) * PI_CONST) * cos((camOrbitAngles.x / 180) * PI_CONST);

	camForwardDir = Vec3Normalize(camForwardDir); //Normalizes the vector

	camForwardDirFlat.x = camForwardDir.x; //Makes the flat vector equal to the normal vector's x coordinate
	camForwardDirFlat.z = camForwardDir.z; //Makes the flat vector equal to the normal vector's z coordinate

	camRightFlat.x = camRight.x; //Makes the flat vector equal to the normal vector's x coordinate
	camRightFlat.z = camRight.z; //Makes the flat vector equal to the normal vector's z coordinate
}

void ConstrainCamAngles() //Constrains the angles of the camera to fit within camMinVertAngle and camMaxVertAngle
{
	if (camOrbitAngles.x < camMinVertAngle) //If it's less than the minimum, set it to the minimum
	{
		camOrbitAngles.x = camMinVertAngle;
	}

	if (camOrbitAngles.x > camMaxVertAngle) //If it's greater than the maximum, set it to the maximum
	{
		camOrbitAngles.x = camMaxVertAngle;
	}
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
	//FORWARD VECTOR
	camForwardDir = Vec3Subtract(camFocusPoint, camPos); //Initial calculation of the Forward Vector (Cross product of the focus point and camera position)
	camForwardDir = Vec3Normalize(camForwardDir); //Normalizes the vector

	//RIGHT VECTOR
	camRight.x = -(camForwardDir.z);
	camRight.y = 0.0f;
	camRight.z = camForwardDir.x;
	camRight = Vec3Normalize(camRight); //Normalizes the vector

	//UP VECTOR
	camUp = Vec3CrossProduct(camForwardDir, camRight); //Calculate Up Vector (Cross product of the forward vector and right vector)
	camUp.y = -(camUp.y); //Flips the Y Value so the camera isn't upside down
	camUp = Vec3Normalize(camUp); //Normalizes the vector
}

void ThirdPersonCamRender(Time time) //Computes the camera position, rotation and such - LOOPED
{
	//Computes the camera's new position, look at position and rotation around the player
	ComputeCamPos(time);

	//CAMERA POSITION CHANGE
	//Changes the position/rotation of the camera
	gluLookAt(	camPos.x, camPos.y, camPos.z,						//Camera X, Y, Z Position
				camFocusPoint.x, camFocusPoint.y, camFocusPoint.z,	//Camera X, Y, Z Focal Point
				camUp.x, camUp.y, camUp.z);							//Camera X, Y, Z Up-Vector
}