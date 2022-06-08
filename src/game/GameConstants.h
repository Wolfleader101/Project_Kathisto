#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"

float MOUSE_SENS;
float WALK_SPEED;
float FLY_SPEED;
float UP_SPEED;
float G_ACCELERATION;
float AIR_DENSITY;
float PHYSICS_TIME_STEP;


extern const int VECTOR_DIRECTIONS_LENGTH;
extern const Vector3 VECTOR_DIRECTIONS[];

extern const Vector3 planeVertexBuffer[]; //Plane Vertexes
extern const Vector3 cubeVertexBuffer[]; //Cube Vertexes

extern const Vector3Int planeIndexBuffer[]; //Plane Face Order
extern const Vector3Int cubeIndexBuffer[]; //Cube Face Order

extern const Mesh planeMesh; //Plane Mesh
extern const Mesh cubeMeshCustColours; //Cube Mesh (Custom Vertex Colours)