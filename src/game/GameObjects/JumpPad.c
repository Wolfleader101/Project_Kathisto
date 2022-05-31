#include "JumpPad.h"

//isReady performs 'cooldown' for player being moved by cube collision - Remove this later
bool isReady = true;
float cooldown = 5.0f;
GameObject* collidingObject = NULL;


const RGBA JumpPadColorBuffer[1] = { {1.0f, 0.0f, 0.85f, 1.0f} };

OnStart OnJumpPadStart(GameObject* gameObject)
{
	gameObject->name = "JumpPad";
	gameObject->mesh = planeMesh;

	gameObject->mesh.colors = JumpPadColorBuffer;
	gameObject->mesh.isUniformColor = true;

	gameObject->transform.position = (Vector3){ 10.0f, .01f, 5.0f };
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f };
	gameObject->rigidBody.useGravity = false;
	gameObject->rigidBody.isTrigger = true;
}

OnUpdate OnJumpPadUpdate(Time time, GameObject* gameObject)
{
	if (!isReady)
	{
		cooldown -= time.deltaTime;

		if (cooldown <= 0)
		{
			cooldown = 5.0f;
			isReady = true;
			collidingObject = NULL;
		}
	}
}

OnFixedUpdate OnJumpPadFixedUpdate(Time time, GameObject* gameObject)
{
	if (!isReady)
		collidingObject->rigidBody.velocity.y += 100.0f * time.deltaTime;

}

OnCollision OnJumpPadCollision(Time time, GameObject* gameObject, GameObject* collisionObject)
{
	if (isReady)
	{
		collidingObject = collisionObject;
		collidingObject->rigidBody.velocity.y = 10.0f;
		isReady = false;
	}
}
