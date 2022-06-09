#include "Cube.h"

const RGBA cubeColorBuffer[] = {
	// front colors
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f},
	// back colors
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f}
};

OnStart OnCubeStart(GameObject* gameObject)
{
	gameObject->name = "Cube";

	gameObject->mesh = cubeMeshCustColours;

	gameObject->mesh.colors = cubeColorBuffer;
	gameObject->mesh.isUniformColor = true;

	gameObject->transform.position = (Vector3){ 5.0f, 10.0f, 5.0f };
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f };
	gameObject->rigidBody.useGravity = true;

	gameObject->rigidBody.isPassive = true;

	gameObject->rigidBody.isStatic = false;
}

OnUpdate OnCubeUpdate(Time time, GameObject* gameObject)
{
	//Vector3* pos = &gameObject->transform.position;

	//float amplitude = 2.0f;
	//float period = 2.0f;

	//float theta = (time.currTime) * period;
	//float distance = sin(theta) / amplitude;

	//float hover = lerp(6.0f, 12.0f, distance);

	//pos->y = hover;


	//Vector3* rot = &gameObject->transform.rotation;
	//rot->x += (time.deltaTime * 20);
	//rot->y += (time.deltaTime * 20);
	//rot->z += (time.deltaTime * 20);


}

OnFixedUpdate OnCubeFixedUpdate(Time time, GameObject* gameObject)
{
}

OnCollision OnCubeCollision(Time time, GameObject* gameObject, GameObject* collisionObject) 
{

}