#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"

void InitRigidBody(RigidBody* RigidBody);
void FixedUpdateGameObjects(Time fixedTime, GameObjectManager* gameObjectManager);
void FixedUpdateGameObject(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject); // caled for physics update
void GravityTransform(Time fixedTime, GameObject* gameObject);
void CalculateBoundingBox(GameObject* gameObject);
void DetectCollision(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject);
