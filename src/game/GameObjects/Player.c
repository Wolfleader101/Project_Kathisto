#include "Player.h"

///////////////////////////////////////////
/////////	SETTING VARIABLES
///////////////////////////////////////////

//Setting the variables to default values

float maxSpeed = 4.0f; //The maximum speed that the player can move at
float maxAcceleration = 10.0f; //The maximum acceleration that the player can achieve

Vector3 desiredPlayerVel = { 0.0f, 0.0f, 0.0f }; //The desired velocity of the player object
Vector3 playerVel = { 0.0f, 0.0f, 0.0f }; //The current velocity of the player object

float rotSmoothSpeed = 4.0f; //The speed at which the player character will rotate

Vector2 playerInput = {0.0f, 0.0f}; //The player movement inputs from the keyboard (Left/Right Movement, Forward/Back Movement)

//Stores the verticies for the player object
const Vector3 playerVertexBuffer[] = {
	{ -0.5f, -0.9f, -0.5f },
	{ 0.5f, -0.9f, -0.5f },
	{ -0.5f,  0.9f, -0.5f },
	{ 0.5f,  0.9f, -0.5f },

	{ 0.5f,  0.9f,  0.5f },
	{ 0.5f, -0.9f,  0.5f },
	{ -0.5f,  0.9f,  0.5f },
	{ -0.5f, -0.9f,  0.5f },
};

//Stores the verticie order (Faces) for the player object
const Vector3Int playerIndexBuffer[] = {
	// front
	{0, 2, 1},
	{1, 3, 2},
	// right
	{1, 3, 4},
	{4, 5, 1},
	// back
	{5, 4, 6},
	{6, 7, 5},
	// left
	{7, 6, 0},
	{0, 2, 6},
	// bottom
	{0, 1, 7},
	{7, 5, 1},
	// top
	{2, 3, 6},
	{6, 4, 3}
};

//Stores the colour data for each verticie for the player object
const RGBA playerColorBuffer[] = {
	// front colors
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f},
	// back colors
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f}
};

//Sets the mesh attributes for the player object
Mesh playerMesh = {
	.points = playerVertexBuffer,
	.indices = playerIndexBuffer,
	.pointSize = 8,
	.indexCount = 36,
	.colors = playerColorBuffer,
	.isUniformColor = false,
	.debug = false
};

///////////////////////////////////////////
/////////	FUNCTIONS
///////////////////////////////////////////

OnStart OnPlayerStart(GameObject* gameObject) //Sets the starting variables of the player object
{
	gameObject->name = "Player"; //Sets object name

	gameObject->mesh = playerMesh; //Sets object mesh
	CalculateMeshBoundBox(&gameObject->mesh); //Calculates the boudning box (AABB) around the mesh

	gameObject->transform.position = (Vector3){0.0f, 1.0f, 0.0f}; //Sets initial position (Transform) of mesh
	gameObject->transform.scale = (Vector3){1.0f, 1.0f, 1.0f}; //Sets initial scale of mesh
}

void CalculatePlayerVelcoity(Time time) //Calculates the velocity of the player each frame
{
	float maxSpeedChange = maxAcceleration * time.deltaTime;

	MovePlayer();

	if (playerVel.x < desiredPlayerVel.x)
	{
		playerVel.x += maxSpeedChange;
	}
	else
		if (playerVel.x > desiredPlayerVel.x)
		{
			playerVel.x -= maxSpeedChange;
		}

	if (playerVel.z < desiredPlayerVel.z)
	{
		playerVel.z += maxSpeedChange;
	}
	else
		if (playerVel.z > desiredPlayerVel.z)
		{
			playerVel.z -= maxSpeedChange;
		}
}

void MovePlayer() //Function to move the player relative to the camera object
{
	if (PLAYERFORWARD_TOGGLE == true) //Moves character forward
	{
		desiredPlayerVel.x = camForwardDirFlat.x * WALK_SPEED;
		desiredPlayerVel.z = camForwardDirFlat.z * WALK_SPEED;
	}

	if (PLAYERBACKWARD_TOGGLE == true) //Moves character backward
	{
		desiredPlayerVel.x = -camForwardDirFlat.x * WALK_SPEED;
		desiredPlayerVel.z = -camForwardDirFlat.z * WALK_SPEED;
	}

	if (PLAYERLEFT_TOGGLE == true) //Moves character left
	{
		desiredPlayerVel.x = -camRightFlat.x * WALK_SPEED;
		desiredPlayerVel.z = -camRightFlat.z * WALK_SPEED;
	}

	if (PLAYERRIGHT_TOGGLE == true) //Moves character right
	{
		desiredPlayerVel.x = camRightFlat.x * WALK_SPEED;
		desiredPlayerVel.z = camRightFlat.z * WALK_SPEED;
	}
}

OnUpdate OnPlayerUpdate(Time time, GameObject* gameObject) //Updates every frame
{
	CalculatePlayerVelcoity(time);

	Vector3 displacement = { //The displacement of the player from their original position
		playerVel.x * time.deltaTime,
		playerVel.y * time.deltaTime,
		playerVel.z * time.deltaTime };
	
	gameObject->transform.position.x += displacement.x;
	gameObject->transform.position.z += displacement.z;
}