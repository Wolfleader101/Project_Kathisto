#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"
#include "game/Physics.h"
#include "game/Rendering.h"
#include "game/GameObject.h"

void UpdateGameObjects(Time time, GameObjectManager* gameObjectManager);
void FixedUpdateGameObjects(Time fixedTime, GameObjectManager* gameObjectManager);