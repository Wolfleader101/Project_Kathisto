#include "GameObjectManager.h"

void InitGameObjectManager(GameObjectManager* gameObjectManager)
{
	const size_t count = 20u;
	gameObjectManager->count = count;
	gameObjectManager->gameObjects = malloc(count * sizeof(GameObject));
	gameObjectManager->boundingBoxes = malloc(count * sizeof(BoudingBox));
	gameObjectManager->lastIndex = 0u;
	gameObjectManager->freeSpace = count;

	if (gameObjectManager->gameObjects == NULL) return;
	for (size_t i = 0; i < count; i++)
	{
		gameObjectManager->gameObjects[i] = malloc(sizeof(GameObject));
		if (gameObjectManager->gameObjects[i] == NULL) return;
		InitGameObject(gameObjectManager->gameObjects[i]);
	}
}

// TODO FIX THIS METHOD??
void GameObjectManagerIncrease(GameObjectManager* gameObjectManager)
{
	const size_t newCount = gameObjectManager->count + (gameObjectManager->count / 2);
	GameObject* temp = realloc(gameObjectManager->gameObjects, newCount * sizeof(GameObject));
	if (temp)
	{
		gameObjectManager->gameObjects = temp;

		for (size_t i = gameObjectManager->count; i < newCount; i++)
		{
			gameObjectManager->gameObjects[i] = malloc(sizeof(GameObject));
			if (gameObjectManager->gameObjects[i] == NULL) return;
			InitGameObject(gameObjectManager->gameObjects[i]);
		}

		gameObjectManager->count += newCount;
		gameObjectManager->freeSpace += newCount;
	}
}

/*
When a GameObject is added:
	add the game object to the end of the game object list at index of count using realloc
	increase count by 1
 */
void GameObjectManagerAdd(GameObjectManager* gameObjectManager, GameObject* gameObject)
{
	if (gameObjectManager->freeSpace == 0)
		GameObjectManagerIncrease(gameObjectManager);

	// set its id to the last index
	gameObject->id = gameObjectManager->lastIndex;

	// set the bounding box
	gameObject->rigidBody.boundingBox.gameObjectId = gameObjectManager->lastIndex;


	// add the address of the bounding box to the array
	gameObjectManager->boundingBoxes[gameObjectManager->lastIndex] = &gameObject->rigidBody.boundingBox;

	// set the last index to the game object to be added
	gameObjectManager->gameObjects[gameObjectManager->lastIndex] = gameObject;

	// then call the on start method
	// NOTE THE ONSTART SHOULD NEVER BE NULL, IF ITS NULL THEN YOU HAVE DONE SOMETHING WRONG, THATS WHY THE IF STATEMENT IS COMMENTED OUT
	//if (gameObjectManager->gameObjects[gameObjectManager->lastIndex].OnStart != NULL)
	gameObjectManager->gameObjects[gameObjectManager->lastIndex]->OnStart(gameObjectManager->gameObjects[gameObjectManager->lastIndex]);


	// calculate bounding box
	CalculateBoundingBox(gameObject);

	gameObjectManager->freeSpace--;
	gameObjectManager->lastIndex++;
}

/*
When a GameObject is removed:
	remove the gameobject from the game object list by setting by freeing it
	for all gameobjects where index > deleted index
	copy the gameobject over to gameobject[i - 1]
	take 1 from count
	freespace add 1
	lastIndex take 1
 */
void GameObjectManagerRemove(GameObjectManager* gameObjectManager, size_t id)
{
	if (gameObjectManager->gameObjects[id] == NULL) return;

	FreeGameObject(gameObjectManager->gameObjects[id]);

	for (size_t i = id + 1; i < gameObjectManager->lastIndex; i++)
	{
		// move the game object pointers
		// this is just copying the pointer -- need to do a deep copy!!!!
		gameObjectManager->gameObjects[i - 1] = gameObjectManager->gameObjects[i];
		gameObjectManager->gameObjects[i - 1]->id = i - 1;

		// move the bounding box pointers
		gameObjectManager->boundingBoxes[i - 1] = gameObjectManager->boundingBoxes[i];
		// TODO FIX THIS ERORR???
		gameObjectManager->boundingBoxes[i - 1]->gameObjectId = i - 1;

		// free the last object
		if (i == gameObjectManager->lastIndex - 1)
		{
			gameObjectManager->gameObjects[i] = NULL;
			gameObjectManager->boundingBoxes[i] = NULL;
		}
	}

	gameObjectManager->boundingBoxes[id] = NULL;

	//gameObjectManager->count--;
	gameObjectManager->freeSpace++;
	gameObjectManager->lastIndex--;
}

GameObject* GameObjectManagerFind(GameObjectManager* gameObjectManager, size_t id)
{
	return gameObjectManager->gameObjects[id];
}
