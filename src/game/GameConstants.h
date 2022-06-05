#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"

extern const float MOUSE_SENS;
extern const float WALK_SPEED;
extern const float FLY_SPEED;
extern const float UP_SPEED;
extern const float G_ACCELERATION;
float AIR_DENSITY;
extern const float PHYSICS_TIME_STEP;


extern const int VECTOR_DIRECTIONS_LENGTH;
extern const Vector3 VECTOR_DIRECTIONS[];

extern const Vector3 planeVertexBuffer[]; //Plane Vertexes
extern const Vector3 cubeVertexBuffer[]; //Cube Vertexes

extern const Vector3Int planeIndexBuffer[]; //Plane Face Order
extern const Vector3Int cubeIndexBuffer[]; //Cube Face Order

extern const Mesh planeMesh; //Plane Mesh
extern const Mesh cubeMeshCustColours; //Cube Mesh (Custom Vertex Colours)