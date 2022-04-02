#include "Player.h"

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

//Sets the starting variables of the player object
OnStart OnPlayerStart(GameObject* gameObject)
{
	gameObject->name = "player"; //Sets object name

	gameObject->mesh = playerMesh; //Sets object mesh
	CalculateMeshBoundBox(&gameObject->mesh); //Calculates the boudning box (AABB) around the mesh

	gameObject->transform.position = (Vector3){ 0.0f, 1.0f, 0.0f }; //Sets initial position (Transform) of mesh
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f }; //Sets initial scale of mesh
}