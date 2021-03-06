#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Used for strcat()
#include <GL/freeglut.h>

#include "game/Game.h"

#include "gui/Gui.h"

#include "Events.h"
#include "math/Vector.h"
#include "loader/model/objLoader.h" //Enables the ability to load basic obj files

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int frame;
extern int timebase;
extern int fps;

extern GLfloat position0[];

extern Time time;
extern Time deltaTime;

extern GameObjectManager gameObjectManager;

/**
 * @brief Initialises all Game Objects to be used
*/
void InitialiseGameObjects();

/**
 * @brief Initialises an OBJ without Groups
*/
void InitialiseOBJ(ObjFile inputOBJ, float r, float g, float b, bool uniformColour, Vector3 transformPosition);

/**
 * @brief Initialises an OBJ with Groups
*/
void InitialiseOBJGroups(ObjFile inputOBJ, float r, float g, float b, bool uniformColour, Vector3 transformPosition);

/**
 * @brief calculate the update time
*/
void CalculateTime(); 

/**
 * @brief calculate the fixed time
*/
void CalculateFixedTime(); 

/**
 * @brief called when window gets resized
*/
void ReshapeWindow(int width, int height); 

/**
 * @brief called every frame
*/
void WindowRender(void); 

/**
 * @brief fixed update called every fixed update step, set in gameConstants
*/
void FixedUpdate(int val);

/**
 * @brief initialise the window with a name
*/
void InitialiseWindow(int* argc, char** argv, char* windowName);

void UpdateSunlight(float sunDir[3], float sunCutoff);