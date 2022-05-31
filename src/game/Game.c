#include "Game.h"

void UpdateGameObjects(Time time, GameObjectManager* gameObjectManager)
{
	for (size_t i = 0; i < gameObjectManager->lastIndex; i++)
	{
		UpdateGameObject(time, gameObjectManager->gameObjects[i]);
	}
}

void FixedUpdateGameObjects(Time fixedTime, GameObjectManager* gameObjectManager)
{
	for (size_t i = 0; i < gameObjectManager->lastIndex; i++)
	{
		FixedUpdateGameObject(fixedTime, gameObjectManager, gameObjectManager->gameObjects[i]);
	}
}