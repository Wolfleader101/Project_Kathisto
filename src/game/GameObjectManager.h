#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"


void InitGameObjectManager(GameObjectManager* gameObjectManager);
void GameObjectManagerIncrease(GameObjectManager* gameObjectManager);
void GameObjectManagerAdd(GameObjectManager* gameObjectManager, GameObject* GameObject);
void GameObjectManagerRemove(GameObjectManager* gameObjectManager, size_t id);
GameObject* GameObjectManagerFind(GameObjectManager* gameObjectManager, size_t id);