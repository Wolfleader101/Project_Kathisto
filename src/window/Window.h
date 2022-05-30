#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "game/Game.h"

#include "gui/Gui.h"

#include "Events.h"
#include "game/GameObjects/Camera.h"
#include "game/GameObjects/CameraThirdPerson.h" //Includes the Third Person Camera
#include "game/GameObjects/Player.h" //Includes access to the player object
#include "math/Vector.h"

#include "game/GameObjects/GameGeometry/DebugGeo.h" //In Charge of building the Debug Geometry 

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
