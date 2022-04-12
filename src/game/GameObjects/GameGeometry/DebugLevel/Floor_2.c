#include "Floor_2.h"

// position of each of the ground points
const Vector3 floor2VertexBuffer[] = {
	{ -1.0f, 0.0f, -1.0f },
	{ -1.0f, 0.0f, 1.0f },
	{ 1.0f,  0.0f, 1.0f },
	{ 1.0f,  0.0f, -1.0f },
};

// index buffer on how to render the points
const Vector3Int floor2IndexBuffer[] = {
	{0, 1, 2},
	{2, 3, 0}
};

// simple RGBA color buffer
const RGBA floor2ColorBuffer[] = { {0.5f, 0.5f, 0.5f, 1.0f} };

// create the mesh
const Mesh floor2Mesh = {
	.points = floor2VertexBuffer,
	.indices = floor2IndexBuffer,
	.pointSize = 4,
	.indexCount = 6,
	.colors = floor2ColorBuffer,
	.isUniformColor = true };

OnStart OnFloor2Start(GameObject* gameObject)
{
	gameObject->name = "Floor_2";
	gameObject->mesh = floor2Mesh;
	gameObject->transform.position = (Vector3){ 190.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}