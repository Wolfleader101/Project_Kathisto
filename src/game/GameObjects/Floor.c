#include "Floor.h"

GameObject floorGameObject = {0};

// position of each of the ground points
const Vector3 floorVertexBuffer[] = {
	{ -1.0f, 0.0f, -1.0f },
	{ -1.0f, 0.0f, 1.0f },
	{ 1.0f,  0.0f, 1.0f },
	{ 1.0f,  0.0f, -1.0f },

};

// index buffer on how to  the points
const Vector3Int floorIndexBuffer[] = {
	{0, 1, 2},
	{2, 3, 0}
};

// simple RGBA color buffer
const RGBA floorColorBuffer[] = { {0.7f, 0.7f, 0.7f, 1.0f} };

// create the mesh
const Mesh floorMesh = {
	.points = floorVertexBuffer,
	.indices = floorIndexBuffer,
	.pointSize = 4,
	.indexCount = 6,
	.colors = floorColorBuffer,
	.isUniformColor = true };

OnStart OnFloorStart(GameObject* gameObject)
{
	gameObject->name = "Floor";
	gameObject->mesh = floorMesh;
	gameObject->transform.scale = (Vector3){ 100.0f, 1.0f, 100.0f };
	CalculateMeshBoundBox(&gameObject->mesh);
}