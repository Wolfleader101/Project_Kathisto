#include "Ceilings.h"

// position of each of the ground points
const Vector3 ceilingVertexBuffer[] = {
	{ -1.0f, 0.0f, -1.0f },
	{ -1.0f, 0.0f, 1.0f },
	{ 1.0f,  0.0f, 1.0f },
	{ 1.0f,  0.0f, -1.0f },
};

// index buffer on how to render the points
const Vector3Int ceilingIndexBuffer[] = {
	{0, 1, 2},
	{2, 3, 0}
};

// simple RGBA color buffer
const RGBA ceiling1ColorBuffer[] = { {0.8f, 0.8f, 0.8f, 1.0f} };

// create the mesh
const Mesh ceilingMesh = {
	.points = ceilingVertexBuffer,
	.indices = ceilingIndexBuffer,
	.pointSize = 4,
	.indexCount = 6,
	.colors = NULL,
	.isUniformColor = true };

OnStart OnCeiling1Start(GameObject* gameObject)
{
	gameObject->name = "Ceiling_1";
	gameObject->mesh = ceilingMesh;

	gameObject->mesh.colors = ceiling1ColorBuffer;

	gameObject->transform.position = (Vector3){ 0.0f, 80.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}

OnStart OnCeiling2Start(GameObject* gameObject)
{
	gameObject->name = "Ceiling_2";
	gameObject->mesh = ceilingMesh;

	gameObject->mesh.colors = ceiling1ColorBuffer;

	gameObject->transform.position = (Vector3){ 190.0f, 80.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}