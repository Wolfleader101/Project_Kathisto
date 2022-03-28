#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "game/Game.h"

#include "gui/Gui.h"

#include "Events.h"
#include "game/GameObjects/Camera.h"
#include "math/Vector.h"


extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int frame;
extern int timebase;
extern int fps;

extern Time time;

extern GameObjectManager gameObjectManager;

// calculate the delta time
void CalculateDeltaTime(); 

// called when window gets resized
void ReshapeWindow(int width, int height); 

// called every frame
void WindowRender(void); 

// initialise the window with a name
void InitialiseWindow(int* argc, char** argv, char* windowName);
