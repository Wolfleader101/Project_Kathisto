#pragma once

#include "game/GameIncludes.h"
#include "game/GameConstants.h"

extern Vector3 cameraForwardDir;
extern Vector3 cameraPos;
extern Vector3 cameraUp;
extern Vector3 cameraMoveDir;

extern Vector2 mousePos;
extern Vector2 mouseDeltaPos;

/**
 * @brief Computes the camera's position
 * @param float deltaTime - The current game delta time
*/
void ComputeCameraPos(float deltaTime); // compute the position of the camera

/**
 * @brief The function which is called to render the camera
 * @param float deltaTime - The current game delta time
*/
void CameraRender(float deltaTime); // called every time the camera should render