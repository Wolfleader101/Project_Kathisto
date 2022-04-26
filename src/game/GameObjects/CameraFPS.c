#include "Camera.h"

Vector3 fpsCamForwardDir = { 0.0f, 0.0f, -1.0f };
Vector3 fpsCameraPos = { 0.0f, 1.8f, 5.0f };
Vector3 fpsCamUp = { 0.0f, 1.0f, 0.0f };
Vector3 fpsCamMoveDir = { 0.0f, 0.0f, 0.0f };

Vector2 fpsMousePos = { 0.0f, 0.0f };
Vector2 fpsMouseDeltaPos = { 0.0f, 0.0f };

//Stores the colour data for each verticie for the player object (Invisible)
const RGBA fpsPlayerColorBuffer[] = {
	// front colors
	{0.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 0.0f, 1.0f},
	// back colors
	{0.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 0.0f, 1.0f}
};

//Sets the mesh attributes for the player object
Mesh playerMesh = {
	.points = playerVertexBuffer,
	.indices = playerIndexBuffer,
	.pointSize = 8,
	.indexCount = 36,
	.colors = fpsPlayerColorBuffer,
	.isUniformColor = true,
	.debug = false
};

OnStart OnFPSCamStart(GameObject* gameObject)
{
	gameObject->name = "Player Cam (FPS)";

	gameObject->mesh = playerMesh;

	CalculateMeshBoundBox(&gameObject->mesh); //Calculates the boudning box (AABB) around the mesh

	gameObject->rigidBody.useGravity = false;

	gameObject->transform.position = (Vector3){ fpsCameraPos.x, fpsCameraPos.y, fpsCameraPos.z };
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f };
}

void ComputeFPSCameraPos(float deltaTime)
{
	// REMEMBER: multiplying by delta time helps create smooth movement

	// calculate the forward/back position
	// new pos = the cams forward dir * (the forward move direction * walk speed)
	Vector3 newPos = Vec3ScalarMultiply(cameraForwardDir, cameraMoveDir.z * (WALK_SPEED * deltaTime));
	// change camera's position
	cameraPos.x += newPos.x;
	//cameraPos.y += newPos.y;
	cameraPos.z += newPos.z;

	// calculate the left/right position
	// a normalised vectors values are between 0 and 1.
	// a cross product of 2 vectors is a perpendicular vector
	// new pos = normalised (cross product of cameraForward pos and Camera Up) * the move left move direction * walk speed)
	newPos = Vec3ScalarMultiply(Vec3Normalize(Vec3CrossProduct(cameraForwardDir, cameraUp)), cameraMoveDir.x * (WALK_SPEED * deltaTime));
	cameraPos.x += newPos.x;
	//cameraPos.y += newPos.y;
	cameraPos.z += newPos.z;

	// calculate the up/down position
	//cameraPos.y += cameraMoveDir.y * (UP_SPEED * deltaTime);

}

void OnFPSCamUpdate(float deltaTime)
{
	// compute the cameras position you can move
	ComputeFPSCameraPos(deltaTime);

	// Cam Position and rotation
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
		cameraPos.x + cameraForwardDir.x, cameraPos.y + cameraForwardDir.y, cameraPos.z + cameraForwardDir.z,
		cameraUp.x, cameraUp.y, cameraUp.z);
}
