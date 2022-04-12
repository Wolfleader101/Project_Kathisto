#include "Floor_1.h"

// position of each of the ground points
const Vector3 floor1VertexBuffer[] = {
	{ -1.0f, 0.0f, -1.0f },
	{ -1.0f, 0.0f, 1.0f },
	{ 1.0f,  0.0f, 1.0f },
	{ 1.0f,  0.0f, -1.0f },
};

// index buffer on how to render the points
const Vector3Int floor1IndexBuffer[] = {
	{0, 1, 2},
	{2, 3, 0}
};

// simple RGBA color buffer
const RGBA floor1ColorBuffer[] = { {0.5f, 0.5f, 0.5f, 1.0f} };

// create the mesh
const Mesh floor1Mesh = {
	.points = floor1VertexBuffer,
	.indices = floor1IndexBuffer,
	.pointSize = 4,
	.indexCount = 6,
	.colors = floor1ColorBuffer,
	.isUniformColor = true };

OnStart OnFloor1Start(GameObject* gameObject)
{
	gameObject->name = "Floor_1";
	gameObject->mesh = floor1Mesh;
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}