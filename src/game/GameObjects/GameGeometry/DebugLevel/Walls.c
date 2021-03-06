#include "Walls.h"

// simple RGBA color buffer
const RGBA wall1ColorBuffer[] = { {1.0f, 0.3f, 0.3f, 1.0f} };
const RGBA wall2ColorBuffer[] = { {0.3f, 1.0f, 0.3f, 1.0f} };
const RGBA wall3ColorBuffer[] = { {0.3f, 0.3f, 1.0f, 1.0f} };
const RGBA wall4ColorBuffer[] = { {0.215f, 0.713f, 0.435f, 1.0f} };
const RGBA wall5ColorBuffer[] = { {0.421f, 0.147f, 0.945f, 1.0f} };

OnStart OnWall1Start(GameObject* gameObject)
{
	gameObject->name = "Wall_1";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall1ColorBuffer;

	gameObject->transform.position = (Vector3){ 0.0f, 40.0f, -60.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 40.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall2Start(GameObject* gameObject)
{
	gameObject->name = "Wall_2";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall2ColorBuffer;

	gameObject->transform.position = (Vector3){ 0.0f, 40.0f, 60.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 40.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall3Start(GameObject* gameObject)
{
	gameObject->name = "Wall_3";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall1ColorBuffer;

	gameObject->transform.position = (Vector3){ 190.0f, 40.0f, -60.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 40.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall4Start(GameObject* gameObject)
{
	gameObject->name = "Wall_4";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall2ColorBuffer;

	gameObject->transform.position = (Vector3){ 190.0f, 40.0f, 60.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 40.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall5Start(GameObject* gameObject)
{
	gameObject->name = "Wall_5";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall3ColorBuffer;

	gameObject->transform.position = (Vector3){ 278.0f, 40.0f, 0.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 60.0f, 1.0f, 40.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall6Start(GameObject* gameObject)
{
	gameObject->name = "Wall_6";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall3ColorBuffer;

	gameObject->transform.position = (Vector3){ -88.0f, 40.0f, 0.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 60.0f, 1.0f, 40.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall7Start(GameObject* gameObject)
{
	gameObject->name = "Wall_7";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall4ColorBuffer;

	gameObject->transform.position = (Vector3){ 88.0f, 60.0f, 0.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 60.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall8Start(GameObject* gameObject)
{
	gameObject->name = "Wall_8";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall4ColorBuffer;

	gameObject->transform.position = (Vector3){ 102.0f, 60.0f, 0.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 60.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall9Start(GameObject* gameObject)
{
	gameObject->name = "Wall_9";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall4ColorBuffer;

	gameObject->transform.position = (Vector3){ 102.0f, 20.0f, -55.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 5.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall10Start(GameObject* gameObject)
{
	gameObject->name = "Wall_10";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall4ColorBuffer;

	gameObject->transform.position = (Vector3){ 88.0f, 20.0f, -55.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 5.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall11Start(GameObject* gameObject)
{
	gameObject->name = "Wall_11";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall4ColorBuffer;

	gameObject->transform.position = (Vector3){ 88.0f, 20.0f, 55.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 5.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall12Start(GameObject* gameObject)
{
	gameObject->name = "Wall_12";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall4ColorBuffer;

	gameObject->transform.position = (Vector3){ 102.0f, 20.0f, 55.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 5.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall13Start(GameObject* gameObject)
{
	gameObject->name = "Wall_13";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall4ColorBuffer;

	gameObject->transform.position = (Vector3){ 102.0f, 20.0f, 0.0f };
	gameObject->transform.rotation = (Vector3){ 0.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 20.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall14Start(GameObject* gameObject)
{
	gameObject->name = "Wall_14";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall4ColorBuffer;

	gameObject->transform.position = (Vector3){ 88.0f, 20.0f, 0.0f };
	gameObject->transform.rotation = (Vector3){ 0.0f, 0.0f, 90.0f };
	gameObject->transform.scale = (Vector3){ 20.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall15Start(GameObject* gameObject)
{
	gameObject->name = "Wall_15";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall5ColorBuffer;

	gameObject->transform.position = (Vector3){ 95.0f, 20.0f, 50.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 7.0f, 1.0f, 20.0f };

	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall16Start(GameObject* gameObject)
{
	gameObject->name = "Wall_16";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall5ColorBuffer;

	gameObject->transform.position = (Vector3){ 95.0f, 20.0f, 20.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 7.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall17Start(GameObject* gameObject)
{
	gameObject->name = "Wall_17";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall5ColorBuffer;

	gameObject->transform.position = (Vector3){ 95.0f, 20.0f, -50.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 7.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}

OnStart OnWall18Start(GameObject* gameObject)
{
	gameObject->name = "Wall_18";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = wall5ColorBuffer;

	gameObject->transform.position = (Vector3){ 95.0f, 20.0f, -20.0f };
	gameObject->transform.rotation = (Vector3){ 90.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 7.0f, 1.0f, 20.0f };


	gameObject->rigidBody.isStatic = true;
}