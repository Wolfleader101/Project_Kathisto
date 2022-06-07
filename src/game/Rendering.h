#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"
#include "loader/model/objStructure.h"


/**
 * @brief initialise a mesh component
 * @param mesh to initialise
*/
void InitMesh(Mesh* mesh);

/**
 * @brief OBJ file to mesh component
 * @param model to load in
 * @param mesh to load data in to
*/
void objToMesh(ObjModel model, Mesh* mesh);


/**
 * @brief draw a mesh in openGL
 * @param time used to draw smoothly
 * @param mesh to draw
*/
void DrawMesh(Time time, Mesh* mesh);

/**
 * @brief draw a gameobject gizmo
 * @param time used tp draw smoothly
 * @param maxSize of the gizmos
*/
void DrawGizmos(Time time, Vector3 maxSize);

/**
 * @brief draw the bounding box of a gameobject
 * @param box to draw
*/
void DrawBoundingBox(BoudingBox box);