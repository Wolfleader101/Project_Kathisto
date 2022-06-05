#include "Teleporters.h"

const RGBA Teleporter1ColorBuffer[1] = { {1.0f, 0.968f, 0.278f} };
const RGBA Teleporter2ColorBuffer[1] = { {0.278f, 1.0f, 0.949f} };
const float maxTeleCooldown = 5.0f;


bool areTeleportersReady = true;
float teleCooldown = 5.0f;


OnStart OnTeleporter1Start(GameObject* gameObject)
{
	gameObject->name = "Teleporter1";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = Teleporter1ColorBuffer;
	gameObject->mesh.isUniformColor = true;

	gameObject->transform.position = (Vector3){ 165.0f, .01f, 15.0f };
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f };
	gameObject->rigidBody.useGravity = false;
	gameObject->rigidBody.isTrigger = true;
}

OnStart OnTeleporter2Start(GameObject* gameObject)
{
	gameObject->name = "Teleporter2";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = Teleporter2ColorBuffer;
	gameObject->mesh.isUniformColor = true;

	gameObject->transform.position = (Vector3){ -30.0f, .01f, 15.0f };
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f };
	gameObject->rigidBody.useGravity = false;
	gameObject->rigidBody.isTrigger = true;
}


OnCollision OnTeleporter1Collision(Time time, GameObject* gameObject, GameObject* collisionObject)
{
	if (areTeleportersReady)
	{
		collisionObject->transform.position = (Vector3){ -30.0f, collisionObject->transform.position.y, 15.0f };

		areTeleportersReady = false;
	}
}

OnCollision OnTeleporter2Collision(Time time, GameObject* gameObject, GameObject* collisionObject)
{
	if (areTeleportersReady)
	{
		collisionObject->transform.position = (Vector3){ 165.0f, collisionObject->transform.position.y, 15.0f };

		areTeleportersReady = false;
	}
}

OnUpdate OnTeleporter1Update(Time time, GameObject* gameObject)
{
	if (!areTeleportersReady)
	{


		teleCooldown -= time.deltaTime;
		if (teleCooldown <= 0)
		{
			teleCooldown = maxTeleCooldown;
			areTeleportersReady = true;
		}
	}

}