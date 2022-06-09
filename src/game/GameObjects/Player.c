#include "Player.h"

///////////////////////////////////////////
/////////	SETTING VARIABLES
///////////////////////////////////////////

//Setting the variables to default values

Vector3 desiredPlayerVel = { 0.0f, 0.0f, 0.0f }; //The desired velocity of the player object

float rotSmoothSpeed = 4.0f; //The speed at which the player character will rotate

Vector2 playerInput = { 0.0f, 0.0f }; //The player movement inputs from the keyboard (Left/Right Movement, Forward/Back Movement)

float jumpCooldown = 1.0f; //The cooldown before a player can jump again after jumping.
float jumpBuffer = 10.0f;

const float MAXPVELOCITY = 10.0f; //Maximum speed at which the player can move along the X and Z axes.
const float SDECAYMULTIPLIER = 0.95f; //Current speed will become this percent of itself every update - slows player when they are not conciously moving in a direction.
float speedMP = 1.5f; //Speed multiplier will reduce to prevent excess speed when multiple keys are held down

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

	gameObject->transform.position = (Vector3){ 0.0f, 15.0f, 0.0f }; //Sets initial position (Transform) of mesh
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f }; //Sets initial scale of mesh

	gameObject->rigidBody.useGravity = true;
}


void MovePlayer(Time time, GameObject* gameObject) //Function to move the player relative to the camera object
{
	gameObject->rigidBody.velocity.x *= SDECAYMULTIPLIER;
	gameObject->rigidBody.velocity.z *= SDECAYMULTIPLIER;

	//Set speedMP to 1.5. This value is reduced by 0.5 for every direction the player is trying to move in (unless directions conflict) this update
	speedMP = 1.5;
	if ((PLAYERFORWARD_TOGGLE && !PLAYERBACKWARD_TOGGLE) || (!PLAYERFORWARD_TOGGLE && PLAYERBACKWARD_TOGGLE)) speedMP -= 0.5;
	if ((PLAYERLEFT_TOGGLE && !PLAYERRIGHT_TOGGLE) || (!PLAYERLEFT_TOGGLE && PLAYERRIGHT_TOGGLE)) speedMP -= 0.5;

	if (PLAYERFORWARD_TOGGLE == true) //Moves character forward
	{
		gameObject->rigidBody.velocity.x += camForwardDirFlat.x * WALK_SPEED * time.deltaTime * speedMP;
		gameObject->rigidBody.velocity.z += camForwardDirFlat.z * WALK_SPEED * time.deltaTime * speedMP;
	}

	if (PLAYERBACKWARD_TOGGLE == true) //Moves character backward
	{
		gameObject->rigidBody.velocity.x += -camForwardDirFlat.x * WALK_SPEED * time.deltaTime * speedMP;
		gameObject->rigidBody.velocity.z += -camForwardDirFlat.z * WALK_SPEED * time.deltaTime * speedMP;
	}

	if (PLAYERLEFT_TOGGLE == true) //Moves character left
	{
		gameObject->rigidBody.velocity.x += -camRightFlat.x * WALK_SPEED * time.deltaTime * speedMP;
		gameObject->rigidBody.velocity.z += -camRightFlat.z * WALK_SPEED * time.deltaTime * speedMP;
	}

	if (PLAYERRIGHT_TOGGLE == true) //Moves character right
	{
		gameObject->rigidBody.velocity.x += camRightFlat.x * WALK_SPEED * time.deltaTime * speedMP;
		gameObject->rigidBody.velocity.z += camRightFlat.z * WALK_SPEED * time.deltaTime * speedMP;
	}

	if (PLAYERJUMP == true && jumpCooldown <= 0 && jumpBuffer > 0) //Makes player jump
	{
		gameObject->rigidBody.velocity.y += 8.0f; //Adds vertical velocity
		jumpCooldown = 2.0f; //Resets jump cooldown (this value seems good as it is slightly longer than up and down motion of jump - prevents infinite jump if collision issue)
		jumpBuffer = 0;
		PLAYERJUMP = false;
	}
	else if (PLAYERJUMP == true) //Reset PLAYERJUMP to off despite cooldown state - this is needed as PLAYERJUMP is not a toggle like other movement
	{
		PLAYERJUMP = false;
	}


	//Caps horizontal velocity to maximum after all movements are updated. Prevents sonic speed.
	if (gameObject->rigidBody.velocity.x > MAXPVELOCITY) gameObject->rigidBody.velocity.x = MAXPVELOCITY;
	else if (gameObject->rigidBody.velocity.x < (-1 * MAXPVELOCITY)) gameObject->rigidBody.velocity.x = (-1 * MAXPVELOCITY);
	if (gameObject->rigidBody.velocity.z > MAXPVELOCITY) gameObject->rigidBody.velocity.z = MAXPVELOCITY;
	else if (gameObject->rigidBody.velocity.z < (-1 * MAXPVELOCITY)) gameObject->rigidBody.velocity.z = (-1 * MAXPVELOCITY);
}

OnFixedUpdate OnPlayerFixedUpdate(Time time, GameObject* gameObject) //Updates every fixed frame
{
	MovePlayer(time, gameObject);

	if (PLAYERJUMP == false && jumpCooldown > 0) //Decrease jumpCooldown to allow for player to jump again when cooldown is 0
	{
		jumpCooldown -= time.deltaTime;
	}

	if (gameObject->rigidBody.onGround) jumpBuffer = 5;
	else jumpBuffer -= 1;
}


//This can be seen as test for jump pad - May want to move this over so code is run from jump pad object
OnCollision OnPlayerCollision(Time time, GameObject* gameObject, GameObject* collisionObject) //Updates every frame
{
}