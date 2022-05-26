#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"

void InitMesh(Mesh* mesh);

void DrawMesh(Time time, Mesh* mesh);
void DrawGizmos(Time time, Vector3 maxSize);
void DrawBoundingBox(BoudingBox box);