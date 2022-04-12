#include "DebugGeo.h" //In Charge of building the Debug Geometry 

void BuildDebugGeo(GameObjectManager* gameObjectManager) //In charge of building the Geometry for the Debug Level
{
	//////////////////////////////
	////	CEILINGS
	//////////////////////////////

	GameObject* ceiling_1 = malloc(sizeof(GameObject));
	InitGameObject(ceiling_1);
	SetupCallbacks(ceiling_1, OnCeiling1Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, ceiling_1);

	GameObject* ceiling_2 = malloc(sizeof(GameObject));
	InitGameObject(ceiling_2);
	SetupCallbacks(ceiling_2, OnCeiling2Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, ceiling_2);

	//////////////////////////////
	////	FLOORS
	//////////////////////////////
	
	GameObject* floor_1 = malloc(sizeof(GameObject));
	InitGameObject(floor_1);
	SetupCallbacks(floor_1, OnFloor1Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, floor_1);

	GameObject* floor_2 = malloc(sizeof(GameObject));
	InitGameObject(floor_2);
	SetupCallbacks(floor_2, OnFloor2Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, floor_2);

	//////////////////////////////
	////	WALLS
	//////////////////////////////

	GameObject* wall_1 = malloc(sizeof(GameObject));
	InitGameObject(wall_1);
	SetupCallbacks(wall_1, OnWall1Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_1);

	GameObject* wall_2 = malloc(sizeof(GameObject));
	InitGameObject(wall_2);
	SetupCallbacks(wall_2, OnWall2Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_2);

	GameObject* wall_3 = malloc(sizeof(GameObject));
	InitGameObject(wall_3);
	SetupCallbacks(wall_3, OnWall3Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_3);

	GameObject* wall_4 = malloc(sizeof(GameObject));
	InitGameObject(wall_4);
	SetupCallbacks(wall_4, OnWall4Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_4);

	GameObject* wall_5 = malloc(sizeof(GameObject));
	InitGameObject(wall_5);
	SetupCallbacks(wall_5, OnWall5Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_5);

	GameObject* wall_6 = malloc(sizeof(GameObject));
	InitGameObject(wall_6);
	SetupCallbacks(wall_6, OnWall6Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_6);

	GameObject* wall_7 = malloc(sizeof(GameObject));
	InitGameObject(wall_7);
	SetupCallbacks(wall_7, OnWall7Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_7);

	GameObject* wall_8 = malloc(sizeof(GameObject));
	InitGameObject(wall_8);
	SetupCallbacks(wall_8, OnWall8Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_8);

	GameObject* wall_9 = malloc(sizeof(GameObject));
	InitGameObject(wall_9);
	SetupCallbacks(wall_9, OnWall9Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_9);

	GameObject* wall_10 = malloc(sizeof(GameObject));
	InitGameObject(wall_10);
	SetupCallbacks(wall_10, OnWall10Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_10);

	GameObject* wall_11 = malloc(sizeof(GameObject));
	InitGameObject(wall_11);
	SetupCallbacks(wall_11, OnWall11Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_11);

	GameObject* wall_12 = malloc(sizeof(GameObject));
	InitGameObject(wall_12);
	SetupCallbacks(wall_12, OnWall12Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_12);

	GameObject* wall_13 = malloc(sizeof(GameObject));
	InitGameObject(wall_13);
	SetupCallbacks(wall_13, OnWall13Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_13);

	GameObject* wall_14 = malloc(sizeof(GameObject));
	InitGameObject(wall_14);
	SetupCallbacks(wall_14, OnWall14Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_14);

	GameObject* wall_15 = malloc(sizeof(GameObject));
	InitGameObject(wall_15);
	SetupCallbacks(wall_15, OnWall15Start, NULL, NULL);
	GameObjectManagerAdd(gameObjectManager, wall_15);
}
