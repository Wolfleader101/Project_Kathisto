#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "Window.h"
#include "game/GameObjects/Camera.h"


void OnKeyDown(unsigned char key, int x, int y); // on key down
void OnKeyUp(unsigned char key, int x, int y); // on key up

void OnSpecialKeyDown(int key, int x, int y); // on special key up
void OnSpecialKeyUp(int key, int x, int y); // on special key up

void OnMouseButton(int button, int state, int x, int y); // on mouse buttons
void OnMouseMove(int x, int y); // on mouse move

