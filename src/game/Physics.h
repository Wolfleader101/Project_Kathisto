#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"


void InitRigidBody(RigidBody* RigidBody);
void FixedUpdateGameObjects(Time fixedTime, GameObjectManager* gameObjectManager);
void FixedUpdateGameObject(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject); // caled for physics update
void GravityTransform(Time fixedTime, GameObject* gameObject);
void PhysicsTransform(Time fixedTime, GameObject* gameObject);
void CalculateBoundingBox(GameObject* gameObject);

GameObject* IsColliding(GameObjectManager* gameObjectManager, GameObject* gameObject);
GameObject* SphereCollision(GameObjectManager* gameObjectManager, GameObject* gameObject);
GameObject* BoxCollision(GameObjectManager* gameObjectManager, GameObject* gameObject);

void CollisionResolution(Time fixedTime, GameObject* gameObject, GameObject* collidingObject);
