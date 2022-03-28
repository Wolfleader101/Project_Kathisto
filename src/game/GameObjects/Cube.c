#include "Cube.h"

GameObject cube = {0};

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

const RGBA cubeColorBuffer[] = {
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

Mesh cubeMesh = {
	.points = cubeVertexBuffer,
	.indices = cubeIndexBuffer,
	.pointSize = 8,
	.indexCount = 36,
	.colors = cubeColorBuffer,
	.isUniformColor = false,
	.debug = false
};

OnStart OnCubeStart(GameObject* gameObject)
{
	gameObject->name = "cube";

	gameObject->mesh = cubeMesh;
	CalculateMeshBoundBox(&gameObject->mesh);

	gameObject->transform.position = (Vector3){ 5.0f, 4.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f };
}

OnUpdate OnCubeUpdate(Time time, GameObject* gameObject)
{
	Vector3* pos = &gameObject->transform.position;

	float amplitude = 2.0f;
	float period = 2.0f;

	float theta = (time.currTime) * period;
	float distance = sin(theta) / amplitude;

	float hover = lerp(6.0f, 12.0f, distance);

	pos->y = hover;


	Vector3* rot = &gameObject->transform.rotation;
	rot->x += (time.deltaTime * 20);
	rot->y += (time.deltaTime * 20);
	rot->z += (time.deltaTime * 20);

}

OnFixedUpdate OnCubeFixedUpdate(Time time, GameObject* gameObject)
{
}