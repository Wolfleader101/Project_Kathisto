#include "Camera.h"

Vector3 cameraForwardDir = { 0.0f, 0.0f, -1.0f };
Vector3 cameraPos = { 0.0f, 1.0f, 5.0f };
Vector3 cameraUp = { 0.0f, 1.0f, 0.0f };
Vector3 cameraMoveDir = { 0.0f, 0.0f, 0.0f };

Vector2 mousePos = { 0.0f, 0.0f };
Vector2 mouseDeltaPos = { 0.0f, 0.0f };


void ComputeCameraPos(float deltaTime)
{
	// REMEMBER: multiplying by delta time helps create smooth movement

	// calculate the forward/back position
	// new pos = the cams forward dir * (the forward move direction * walk speed)
	Vector3 newPos = Vec3ScalarMultiply(cameraForwardDir, cameraMoveDir.z * (WALK_SPEED * deltaTime));
	// change camera's position
	cameraPos.x += newPos.x;
	cameraPos.y += newPos.y;
	cameraPos.z += newPos.z;

	// calculate the left/right position
	// a normalised vectors values are between 0 and 1.
	// a cross product of 2 vectors is a perpendicular vector
	// new pos = normalised (cross product of cameraForward pos and Camera Up) * the move left move direction * walk speed)
	newPos = Vec3ScalarMultiply(Vec3Normalize(Vec3CrossProduct(cameraForwardDir, cameraUp)), cameraMoveDir.x * (WALK_SPEED * deltaTime));
	cameraPos.x += newPos.x;
	cameraPos.y += newPos.y;
	cameraPos.z += newPos.z;

	// calculate the up/down position
	cameraPos.y += cameraMoveDir.y * (UP_SPEED * deltaTime);

}

void CameraRender(float deltaTime)
{
	// compute the cameras position you can move
	ComputeCameraPos(deltaTime);

	// Cam Position and rotation
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
		cameraPos.x + cameraForwardDir.x, cameraPos.y + cameraForwardDir.y, cameraPos.z + cameraForwardDir.z,
		cameraUp.x, cameraUp.y, cameraUp.z);
}
