#include "Walls.h"

// position of each of the ground points
const Vector3 wallVertexBuffer[] = {
	{ -1.0f, 0.0f, -1.0f },
	{ -1.0f, 0.0f, 1.0f },
	{ 1.0f,  0.0f, 1.0f },
	{ 1.0f,  0.0f, -1.0f },
};

// index buffer on how to render the points
const Vector3Int wallIndexBuffer[] = {
	{0, 1, 2},
	{2, 3, 0}
};

// simple RGBA color buffer
const RGBA wall1ColorBuffer[] = { {1.0f, 0.3f, 0.3f, 1.0f} };
const RGBA wall2ColorBuffer[] = { {0.3f, 1.0f, 0.3f, 1.0f} };
const RGBA wall3ColorBuffer[] = { {0.3f, 0.3f, 1.0f, 1.0f} };

// create the mesh
const Mesh wallMesh = {
	.points = wallVertexBuffer,
	.indices = wallIndexBuffer,
	.pointSize = 4,
	.indexCount = 6,
	.colors = NULL,
	.isUniformColor = true };

OnStart OnWall1Start(GameObject* gameObject)
{
	gameObject->name = "Wall_1";
	gameObject->mesh = wallMesh;

	gameObject->mesh.colors = wall1ColorBuffer;

	gameObject->transform.position = (Vector3){ 0.0f, 40.0f, -60.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 40.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}

OnStart OnWall2Start(GameObject* gameObject)
{
	gameObject->name = "Wall_2";
	gameObject->mesh = wallMesh;

	gameObject->mesh.colors = wall2ColorBuffer;

	gameObject->transform.position = (Vector3){ 0.0f, 40.0f, 60.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 40.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}

OnStart OnWall3Start(GameObject* gameObject)
{
	gameObject->name = "Wall_3";
	gameObject->mesh = wallMesh;

	gameObject->mesh.colors = wall1ColorBuffer;

	gameObject->transform.position = (Vector3){ 190.0f, 40.0f, -60.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 40.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}

OnStart OnWall4Start(GameObject* gameObject)
{
	gameObject->name = "Wall_4";
	gameObject->mesh = wallMesh;

	gameObject->mesh.colors = wall2ColorBuffer;

	gameObject->transform.position = (Vector3){ 190.0f, 40.0f, 60.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 40.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}

OnStart OnWall5Start(GameObject* gameObject)
{
	gameObject->name = "Wall_5";
	gameObject->mesh = wallMesh;

	gameObject->mesh.colors = wall3ColorBuffer;

	gameObject->transform.position = (Vector3){ 278.0f, 40.0f, 0.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 60.0f, 1.0f, 40.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}

OnStart OnWall6Start(GameObject* gameObject)
{
	gameObject->name = "Wall_6";
	gameObject->mesh = wallMesh;

	gameObject->mesh.colors = wall3ColorBuffer;

	gameObject->transform.position = (Vector3){ -88.0f, 40.0f, 0.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 60.0f, 1.0f, 40.0f };

	CalculateMeshBoundBox(&gameObject->mesh);
}