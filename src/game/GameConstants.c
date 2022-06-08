#include "GameConstants.h"

float MOUSE_SENS = 0.001f;
float WALK_SPEED = 35.0f;
float FLY_SPEED = 15.0f;
float UP_SPEED = 10.0f;
float AIR_DENSITY = 1.225f;

float G_ACCELERATION = 9.81f;
float PHYSICS_TIME_STEP = 20; // in ms

const int VECTOR_DIRECTIONS_LENGTH = 6;
const Vector3 VECTOR_DIRECTIONS[] =
{
	{0, 1, 0}, // up
	{0, -1, 0}, // down
	{1, 0, 0}, // left
	{-1, 0, 0}, // right
	{0, 0, 1}, //forward
	{0, 0, -1}, // back
};

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
	{1, 5, 3},
	{3, 4, 5},
	// back
	{5, 4, 6},
	{6, 5, 7},
	// left
	{7, 6, 2},
	{2, 0, 7},
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