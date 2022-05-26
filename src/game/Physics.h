#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"


void InitRigidBody(RigidBody* RigidBody);
void FixedUpdateGameObject(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject); // caled for physics update
void GravityTransform(Time fixedTime, GameObject* gameObject);
void PhysicsTransform(Time fixedTime, GameObject* gameObject, CollisionData collisionData);
void CalculateBoundingBox(GameObject* gameObject);

CollisionData IsColliding(GameObjectManager* gameObjectManager, GameObject* gameObject);
CollisionData SphereCollision(GameObjectManager* gameObjectManager, GameObject* gameObject);
CollisionData BoxCollision(GameObjectManager* gameObjectManager, GameObject* gameObject);

void CollisionResolution(Time fixedTime, GameObject* gameObject, CollisionData collisionData);
