#include "Player.h"

///////////////////////////////////////////
/////////	SETTING VARIABLES
///////////////////////////////////////////

//Setting the variables to default values

Vector3 desiredPlayerVel = { 0.0f, 0.0f, 0.0f }; //The desired velocity of the player object

float rotSmoothSpeed = 4.0f; //The speed at which the player character will rotate

Vector2 playerInput = { 0.0f, 0.0f }; //The player movement inputs from the keyboard (Left/Right Movement, Forward/Back Movement)

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
	CalculateBoundingBox(&gameObject->mesh); //Calculates the boudning box (AABB) around the mesh

	gameObject->transform.position = (Vector3){ 0.0f, 10.0f, 0.0f }; //Sets initial position (Transform) of mesh
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f }; //Sets initial scale of mesh

	gameObject->rigidBody.useGravity = true;
}


void MovePlayer(Time time, GameObject* gameObject) //Function to move the player relative to the camera object
{
	if (PLAYERFORWARD_TOGGLE == true) //Moves character forward
	{
		gameObject->rigidBody.velocity.x += camForwardDirFlat.x * WALK_SPEED * time.deltaTime;
		gameObject->rigidBody.velocity.z += camForwardDirFlat.z * WALK_SPEED * time.deltaTime;
	}

	if (PLAYERBACKWARD_TOGGLE == true) //Moves character backward
	{
		gameObject->rigidBody.velocity.x += -camForwardDirFlat.x * WALK_SPEED * time.deltaTime;
		gameObject->rigidBody.velocity.z += -camForwardDirFlat.z * WALK_SPEED * time.deltaTime;
	}

	if (PLAYERLEFT_TOGGLE == true) //Moves character left
	{
		gameObject->rigidBody.velocity.x += -camRightFlat.x * WALK_SPEED * time.deltaTime;
		gameObject->rigidBody.velocity.z += -camRightFlat.z * WALK_SPEED * time.deltaTime;
	}

	if (PLAYERRIGHT_TOGGLE == true) //Moves character right
	{
		gameObject->rigidBody.velocity.x += camRightFlat.x * WALK_SPEED * time.deltaTime;
		gameObject->rigidBody.velocity.z += camRightFlat.z * WALK_SPEED * time.deltaTime;
	}
}

OnFixedUpdate OnPlayerFixedUpdate(Time time, GameObject* gameObject) //Updates every fixed frame
{
	MovePlayer(time, gameObject);
}

//isReady performs 'cooldown' for player being moved by cube collision - Remove this later
bool isReady = true;
float cooldown = 5.0f;

//This can be seen as test for jump pad - May want to move this over so code is run from jump pad object
OnCollision OnPlayerCollision(Time time, GameObject* gameObject, GameObject* collisionObject) //Updates every frame
{
	printf("TEST");

	if (isReady) 
	{
		gameObject->transform.position.y += 30;
		isReady = false;
	}
}