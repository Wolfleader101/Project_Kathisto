#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"

/////////////////////////////////////////
////	LEVEL GEOMETRY HEADERS
/////////////////////////////////////////

//CEILINGS
#include "game/GameObjects/GameGeometry/DebugLevel/Ceilings.h"

//FLOORS
#include "game/GameObjects/GameGeometry/DebugLevel/Floors.h"

//WALLS
#include "game/GameObjects/GameGeometry/DebugLevel/Walls.h"

/////////////////////////////////////////
////	BUILDING FUCNTIONS
/////////////////////////////////////////

/**
 * @brief Function which builds all of the Debug Geometry
 * @param GameObjectManager* gameObjectManager - Input game object manager
*/
void BuildDebugGeo(GameObjectManager* gameObjectManager); //In charge of building the Geometry for the Debug Level