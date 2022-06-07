#pragma once

#include <stdlib.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"


#include <window/Events.h>
#include <math/Vector.h>
#include <game/Game.h>
#include "game/GameConstants.h"


extern struct ImGuiContext* ctx; // IMGUI Context
extern struct ImGuiIO* io; // IMGUI IO

/**
 * @brief initialise the GUI
*/
void GuiInit();

/**
 * @brief Free the GUI on game end
*/
void GuiFree();

/**
 * @brief called every update to loop over game objects
 * @param gameObjectManager 
*/
void GuiUpdate(GameObjectManager* gameObjectManager);

/**
 * @brief called to render the GUI
*/
void GuiRender();

/**
 * @brief draw the debug menu
 * @param gameObjectManager to loop over all gameobjects
*/
void DebugMenu(GameObjectManager* gameObjectManager); 

/**
 * @brief the panel for a gameobject
 * @param gameObject pointer to use
*/
void GameObjectPanel(GameObject* gameObject);

/**
 * @brief the widget for a transform comp
 * @param transform component to use
*/
void TransformWidget(Transform* transform);


/**
 * @brief the rigidbody widget
 * @param rigidBody component to use
*/
void RigidBodyWidget(RigidBody* rigidBody);

/**
 * @brief the mesh widget
 * @param mesh component to use
*/
void MeshWidget(Mesh* mesh);