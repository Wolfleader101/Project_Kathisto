#include "math/Vector.h"
#include "game/Game.h"

#pragma once

extern const float MOUSE_SENS;
extern const float WALK_SPEED;
extern const float SPRINT_SPEED;
extern const float UP_SPEED;
extern const float G_ACCELERATION;
extern const float T_VELOCITY;

extern const int shiftKey; //Sets the default state of the Shift Key to a glutGetModifier() value
extern const int crtlKey; //Sets the default state of the Ctrl Key to a glutGetModifier() value
extern const int altKey; //Sets the default state of the Alt Key to a glutGetModifier() value

extern const Vector3 playerVertexBuffer[]; //Player Vertexes
extern const Vector3 planeVertexBuffer[]; //Plane Vertexes
extern const Vector3 cubeVertexBuffer[]; //Cube Vertexes

extern const Vector3Int playerIndexBuffer[]; //Player Face Order
extern const Vector3Int planeIndexBuffer[]; //Plane Face Order
extern const Vector3Int cubeIndexBuffer[]; //Cube Face Order

extern const Mesh planeMesh; //Plane Mesh
extern const Mesh cubeMeshCustColours; //Cube Mesh (Custom Vertex Colours)