#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameConstants.h"

/**
 * @brief initialise a rigidbody and all of its attributes
 * @param RigidBody to initialise
*/
void InitRigidBody(RigidBody* RigidBody);

/**
 * @brief called for physics update at a fixed step
 * @param fixedTime to update smoothly
 * @param gameObjectManager with list of gameobjects to update
 * @param gameObject to fixed update
*/
void FixedUpdateGameObject(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject);

/**
 * @brief function to apply gravity to a gameobject, which also dynamically calculates terminal velocity of the game object
 * @param fixedTime to apply gravity smoothly
 * @param gameObject to apply gravity too
*/
void GravityTransform(Time fixedTime, GameObject* gameObject);

/**
 * @brief physics transforms to apply drag and friction to gameobjects
 * @param fixedTime to apply transformations smoothly
 * @param gameObject to apply transforms
 * @param collisionData to check if on ground or if colliding
*/
void PhysicsTransform(Time fixedTime, GameObject* gameObject, CollisionData collisionData);

/**
 * @brief calculate the bounding box of a gameobject based on mesh
 * @param gameObject to calculate bounding box of
*/
void CalculateBoundingBox(GameObject* gameObject);

/**
 * @brief check if the gameobject is colliding with another gameobject
 * @param gameObjectManager to loop over and compare
 * @param gameObject to check against
 * @return collision data containing information for collision resolution
*/
void IsColliding(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject);

/**
 * @brief check for collision using sphere collision detection, if gameobject is sphere
 * @param gameObjectManager to loop over and compare
 * @param gameObject to check against
 * @return collision data containing information for collision resolution
*/
void SphereCollision(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject);

/**
 * @brief check for collision using AABB detection
 * @param gameObjectManager to loop voer and compare
 * @param gameObject to check against
 * @return collision data containing information for collision resolution
*/
void BoxCollision(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject);

/**
 * @brief resolve the resolution by correctly adjusting the gameobject on collision
 * @param fixedTime to update smoothly
 * @param gameObject to update
 * @param collisionData containg information about the collision
*/
void CollisionResolution(Time fixedTime, GameObject* gameObject, CollisionData collisionData);
