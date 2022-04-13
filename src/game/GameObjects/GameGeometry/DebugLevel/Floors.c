#include "Floors.h"

// simple RGBA color buffer
const RGBA floor1ColorBuffer[] = { {0.5f, 0.5f, 0.5f, 1.0f} };

OnStart OnFloor1Start(GameObject* gameObject)
{
	gameObject->name = "Floor_1";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = floor1ColorBuffer;

	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };
}

OnStart OnFloor2Start(GameObject* gameObject)
{
	gameObject->name = "Floor_2";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = floor1ColorBuffer;

	gameObject->transform.position = (Vector3){ 190.0f, 0.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };
}

OnStart OnFloor3Start(GameObject* gameObject)
{
	gameObject->name = "Floor_3";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = floor1ColorBuffer;

	gameObject->transform.position = (Vector3){ 95.0f, 0.0f, 35.0f };
	gameObject->transform.scale = (Vector3){ 7.0f, 1.0f, 15.0f };
}

OnStart OnFloor4Start(GameObject* gameObject)
{
	gameObject->name = "Floor_4";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = floor1ColorBuffer;

	gameObject->transform.position = (Vector3){ 95.0f, 0.0f, -35.0f };
	gameObject->transform.scale = (Vector3){ 7.0f, 1.0f, 15.0f };
}