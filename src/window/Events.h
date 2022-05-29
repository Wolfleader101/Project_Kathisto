#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <GL/freeglut.h>

#include "Window.h"
#include "game/GameObjects/Camera.h"
#include "game/GameObjects/CameraThirdPerson.h"
#include "game/GameObjects/Player.h"

extern bool USE_MENU_CURSOR_CURSOR;
extern bool TOGGLE_MENU;

extern bool PLAYERFORWARD_TOGGLE;
extern bool PLAYERBACKWARD_TOGGLE;
extern bool PLAYERLEFT_TOGGLE;
extern bool PLAYERRIGHT_TOGGLE;

extern bool EXIT_PROGRAM;

Vector2 mouseInputs; //Stores Mouse Inputs

void OnKeyDown(unsigned char key, int x, int y); // on key down
void OnKeyUp(unsigned char key, int x, int y); // on key up

void OnSpecialKeyDown(int key, int x, int y); // on special key up
void OnSpecialKeyUp(int key, int x, int y); // on special key up

void OnMouseButton(int button, int state, int x, int y); // on mouse buttons
void OnMouseMove(int x, int y); // on mouse move

