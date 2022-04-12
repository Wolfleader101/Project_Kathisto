#include "DebugGeo.h" //In Charge of building the Debug Geometry 

void BuildDebugGeo(GameObjectManager* gameObjectManager) //In charge of building the Geometry for the Debug Level
{
	GameObject* floor_1 = malloc(sizeof(GameObject));
	InitGameObject(floor_1);
	SetupCallbacks(floor_1, OnFloor1Start, NULL, NULL);
	GameObjectManagerAdd(&gameObjectManager, floor_1);

	GameObject* floor_2 = malloc(sizeof(GameObject));
	InitGameObject(floor_2);
	SetupCallbacks(floor_2, OnFloor2Start, NULL, NULL);
	GameObjectManagerAdd(&gameObjectManager, floor_2);
}
