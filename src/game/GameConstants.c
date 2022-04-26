#include "GameConstants.h"

const float MOUSE_SENS = 0.001f;
const float WALK_SPEED = 15.0f;
const float SPRINT_SPEED = 25.0f;
const float UP_SPEED = 10.0f;
const float G_ACCELERATION = 9.8;
const float T_VELOCITY = 53;

const int shiftKey = GLUT_ACTIVE_SHIFT; //Sets the default state of the Shift Key to a glutGetModifier() value
const int crtlKey = GLUT_ACTIVE_CTRL; //Sets the default state of the Ctrl Key to a glutGetModifier() value
const int altKey = GLUT_ACTIVE_ALT; //Sets the default state of the Alt Key to a glutGetModifier() value

///////////////////////////////////////
////	VERTEX BUFFERS
///////////////////////////////////////

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

//Plane Vertexes
const Vector3 planeVertexBuffer[] = {
	{ -1.0f, 0.0f, -1.0f },
	{ -1.0f, 0.0f, 1.0f },
	{ 1.0f,  0.0f, 1.0f },
	{ 1.0f,  0.0f, -1.0f },
};

//Cube Vertexes
const Vector3 cubeVertexBuffer[] = {
	{ -1.0f, -1.0f, -1.0f },
	{ 1.0f, -1.0f, -1.0f },
	{ -1.0f,  1.0f, -1.0f },
	{ 1.0f,  1.0f, -1.0f },

	{ 1.0f,  1.0f,  1.0f },
	{ 1.0f, -1.0f,  1.0f },
	{ -1.0f,  1.0f,  1.0f },
	{ -1.0f, -1.0f,  1.0f },
};

///////////////////////////////////////
////	FACE BUFFERS
///////////////////////////////////////

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

//Plane Face Order
const Vector3Int planeIndexBuffer[] = {
	{0, 1, 2},
	{2, 3, 0}
};

//Cube Face Order
const Vector3Int cubeIndexBuffer[] = {
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

///////////////////////////////////////
////	MESHES
///////////////////////////////////////

//Plane Mesh
const Mesh planeMesh = {
	.points = planeVertexBuffer,
	.indices = planeIndexBuffer,
	.pointSize = 4,
	.indexCount = 6,
	.colors = NULL,
	.isUniformColor = true };

//Cube Mesh (Custom Vertex Colours)
const Mesh cubeMeshCustColours = {
	.points = cubeVertexBuffer,
	.indices = cubeIndexBuffer,
	.pointSize = 8,
	.indexCount = 36,
	.isUniformColor = false,
	.debug = false
};