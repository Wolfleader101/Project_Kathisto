#include "GameConstants.h"

const float MOUSE_SENS = 0.001f;
const float WALK_SPEED = 15.0f;
const float UP_SPEED = 10.0f;
const float G_ACCELERATION = 9.8f;
const float T_VELOCITY = 53.0f;
const float PHYSICS_TIME_STEP = 20; // in ms

///////////////////////////////////////
////	VERTEX BUFFERS
///////////////////////////////////////

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