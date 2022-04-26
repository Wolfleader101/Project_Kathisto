#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "math/Vector.h"
#include "game/GameConstants.h"

extern Vector3 fpsCamForwardDir;
extern Vector3 fpsCameraPos;
extern Vector3 fpsCamUp;
extern Vector3 fpsCamMoveDir;

extern Vector2 fpsMousePos;
extern Vector2 fpsMouseDeltaPos;

OnStart OnFPSCamStart(GameObject* gameObject); //Creates the player's bounding box and sets their starting variables
void ComputeFPSCameraPos(float deltaTime); // compute the position of the camera
OnUpdate OnFPSCamUpdate(float deltaTime); // called every time the camera should render