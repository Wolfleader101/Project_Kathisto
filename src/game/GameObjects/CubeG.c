#include "CubeG.h"

const RGBA cubeGColorBuffer[] = {
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

OnStart OnCubeGStart(GameObject* gameObject)
{
	gameObject->name = "CubeG";

	gameObject->mesh = cubeMeshCustColours;

	gameObject->mesh.colors = cubeGColorBuffer;

	gameObject->rigidBody.useGravity = true;

	gameObject->transform.position = (Vector3){ 5.0f, 30.0f, -5.0f };
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f };

}