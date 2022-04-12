#include "Floors.h"

// position of each of the ground points
const Vector3 floorVertexBuffer[] = {
	{ -1.0f, 0.0f, -1.0f },
	{ -1.0f, 0.0f, 1.0f },
	{ 1.0f,  0.0f, 1.0f },
	{ 1.0f,  0.0f, -1.0f },
};

// index buffer on how to render the points
const Vector3Int floorIndexBuffer[] = {
	{0, 1, 2},
	{2, 3, 0}
};

// simple RGBA color buffer
const RGBA floor1ColorBuffer[] = { {0.5f, 0.5f, 0.5f, 1.0f} };

// create the mesh
const Mesh floorMesh = {
	.points = floorVertexBuffer,
	.indices = floorIndexBuffer,
	.pointSize = 4,
	.indexCount = 6,
	.colors = NULL,
	.isUniformColor = true };

OnStart OnFloor1Start(GameObject* gameObject)
{
	gameObject->name = "Floor_1";
	gameObject->mesh = floorMesh;

	gameObject->mesh.colors = floor1ColorBuffer;

	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}

OnStart OnFloor2Start(GameObject* gameObject)
{
	gameObject->name = "Floor_2";
	gameObject->mesh = floorMesh;

	gameObject->mesh.colors = floor1ColorBuffer;

	gameObject->transform.position = (Vector3){ 190.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}