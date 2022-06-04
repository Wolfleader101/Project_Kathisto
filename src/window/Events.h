#pragma once

#include "includes.h"

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

extern bool FREE_CAM;

Vector2 mouseInputs; //Stores Mouse Inputs

/**
 * @brief On key down event
 * @param key that was pressed
 * @param x position of mouse
 * @param y position of mouse
*/
void OnKeyDown(unsigned char key, int x, int y);

/**
 * @brief on key up event
 * @param key that was released
 * @param x position of mouse
 * @param y position of mouse
*/
void OnKeyUp(unsigned char key, int x, int y);

/**
 * @brief on special key down (function keys) event
 * @param key that was pressed
 * @param x position of mouse
 * @param y position of mouse
*/
void OnSpecialKeyDown(int key, int x, int y);

/**
 * @brief on special key up (function keys) event
 * @param key that was released
 * @param x position of mouse
 * @param y position of mouse
*/
void OnSpecialKeyUp(int key, int x, int y);

/**
 * @brief on mouse move event
 * @param button that was clicked
 * @param state of the click
 * @param x position of mouse
 * @param y position of mouse
*/
void OnMouseButton(int button, int state, int x, int y);

/**
 * @brief on mouse move event
 * @param x position of mouse
 * @param y position of mouse
*/
void OnMouseMove(int x, int y);

void DisplayGroupPhoto(const char* imgName, int imgWidth, int imgHeight, int channelsInFile, int numOfDesiredChannels); //Displays the group photo when exiting the program
