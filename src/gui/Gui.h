#pragma once

#include <stdlib.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

#include <game/Game.h>


extern struct ImGuiContext* ctx; // IMGUI Context
extern struct ImGuiIO* io; // IMGUI IO

void GuiInit(); // initialise the GUI

void GuiFree(); // Free the GUI on game end

void GuiUpdate(GameObjectManager* gameObjectManager); // called on Update

void GuiRender(); // called to render the GUI

void DebugMenu(GameObjectManager* gameObjectManager); // the Debug Menu

