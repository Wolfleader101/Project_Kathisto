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
}
