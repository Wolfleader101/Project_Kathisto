#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "game/Game.h"

#include "gui/Gui.h"

#include "Events.h"
#include "math/Vector.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int frame;
extern int timebase;
extern int fps;

extern Time time;
extern Time deltaTime;

extern GameObjectManager gameObjectManager;

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
