#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"

extern float MOUSE_SENS;
extern float WALK_SPEED;
extern float FLY_SPEED;
extern float UP_SPEED;
extern float G_ACCELERATION;
extern float AIR_DENSITY;
extern float PHYSICS_TIME_STEP;
extern bool PAUSE_PHYSICS;
extern bool SHOW_COLLIDERS;


extern const int VECTOR_DIRECTIONS_LENGTH;
extern const Vector3 VECTOR_DIRECTIONS[];

extern const Vector3 planeVertexBuffer[]; //Plane Vertexes
extern const Vector3 cubeVertexBuffer[]; //Cube Vertexes

extern const Vector3Int planeIndexBuffer[]; //Plane Face Order
extern const Vector3Int cubeIndexBuffer[]; //Cube Face Order

extern const Mesh planeMesh; //Plane Mesh
extern const Mesh cubeMesh; //Plane Mesh
extern const Mesh cubeMeshCustColours; //Cube Mesh (Custom Vertex Colours)