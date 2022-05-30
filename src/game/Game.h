#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"
#include "game/Physics.h"
#include "game/Rendering.h"
#include "game/GameObject.h"


/**
 * @brief update all gameobjects in a game object manager
 * @param time to update smoothly
 * @param gameObjectManager with list of gameobjects to update
*/
void UpdateGameObjects(Time time, GameObjectManager* gameObjectManager);

/**
 * @brief physics update all gameobjects in a game object manager
 * @param fixedTime to update smoothly with fixed time
 * @param gameObjectManager with list of gameobjects to update
*/
void FixedUpdateGameObjects(Time fixedTime, GameObjectManager* gameObjectManager);
