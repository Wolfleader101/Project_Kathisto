#include "Ceilings.h"

// simple RGBA color buffer
const RGBA ceiling1ColorBuffer[] = { {0.8f, 0.8f, 0.8f, 1.0f} };
const RGBA ceiling2ColorBuffer[] = { {0.1f, 0.1f, 0.1f, 1.0f} };

OnStart OnCeiling1Start(GameObject* gameObject)
{
	gameObject->name = "Ceiling_1";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = ceiling1ColorBuffer;

	gameObject->transform.position = (Vector3){ 0.0f, 80.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };
	
}

OnStart OnCeiling2Start(GameObject* gameObject)
{
	gameObject->name = "Ceiling_2";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = ceiling1ColorBuffer;

	gameObject->transform.position = (Vector3){ 190.0f, 80.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 88.0f, 1.0f, 60.0f };
		
}

OnStart OnCeiling3Start(GameObject* gameObject)
{
	gameObject->name = "Ceiling_3";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = ceiling2ColorBuffer;

	gameObject->transform.position = (Vector3){ 95.0f, 40.0f, -35.0f };
	gameObject->transform.scale = (Vector3){ 7.0f, 1.0f, 15.0f };
		
}

OnStart OnCeiling4Start(GameObject* gameObject)
{
	gameObject->name = "Ceiling_4";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = ceiling2ColorBuffer;

	gameObject->transform.position = (Vector3){ 95.0f, 40.0f, 35.0f };
	gameObject->transform.scale = (Vector3){ 7.0f, 1.0f, 15.0f };
		
}