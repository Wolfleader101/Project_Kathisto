#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameObject.h"

/**
 * @brief initialise a game object manager struct
 * @param gameObjectManager to initialise
*/
void InitGameObjectManager(GameObjectManager* gameObjectManager);

/**
 * @brief Increase the size of the gameobject manager by 2x
 * @param gameObjectManager to increase size of
*/
void GameObjectManagerIncrease(GameObjectManager* gameObjectManager);

/**
 * @brief when a GameObject is added, add the game object to the end of the game object list at index of count using realloc and count by 1
 * @param gameObjectManager to add gameobject too
 * @param GameObject  to add to gameobject manager
*/
void GameObjectManagerAdd(GameObjectManager* gameObjectManager, GameObject* GameObject);

/**
 * @brief When a GameObject is removed, remove from array by freeing it
 * for all gameobjects where index > deleted index
 * copy the gameobject over to gameobject[i - 1]
 * take 1 from count, freespace add 1, lastIndex take 1
 * @param gameObjectManager to remove gameobject from
 * @param id of gameobject to remove
*/
void GameObjectManagerRemove(GameObjectManager* gameObjectManager, size_t id);

/**
 * @brief find a gameobject by id
 * @param gameObjectManager to find in
 * @param id of gameobject to find
 * @return the gameobject if found, else NULL
*/
GameObject* GameObjectManagerFind(GameObjectManager* gameObjectManager, size_t id);


/**
 * @brief find a gameobject by name
 * @param gameObjectManager to find gameobject in
 * @param name to search for
 * @return the gameobject if found, else NULL
*/
GameObject* GameObjectManagerFindByName(GameObjectManager* gameObjectManager, char* name);