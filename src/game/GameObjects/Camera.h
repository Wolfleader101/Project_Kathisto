#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "math/Vector.h"
#include "game/GameConstants.h"



extern Vector3 cameraForwardDir;
extern Vector3 cameraPos;
extern Vector3 cameraUp;
extern Vector3 cameraMoveDir;

extern Vector2 mousePos;
extern Vector2 mouseDeltaPos;


void ComputeCameraPos(float deltaTime); // compute the position of the camera
void CameraRender(float deltaTime); // called every time the camera should render