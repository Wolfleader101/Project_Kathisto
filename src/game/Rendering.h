#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"

#include "includes.h"

/**
 * @brief initialise a mesh component
 * @param mesh to initialise
*/
void InitMesh(Mesh* mesh);

/**
 * @brief initialise a texture
 * @param texture texture to initialise
*/
void InitTexture(Texture* texture);

/**
 * @brief load in a texture to a texture object
 * @param file of texture
 * @param texture to load data into
*/
void LoadTexture(char* file, Texture* tex);

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