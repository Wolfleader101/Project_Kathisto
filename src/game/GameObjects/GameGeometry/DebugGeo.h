#include <stdlib.h>
#include <stdio.h>

#include "game/Game.h"

#include "math/Vector.h"

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

void BuildDebugGeo(GameObjectManager* gameObjectManager); //In charge of building the Geometry for the Debug Level