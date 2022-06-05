#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"

#include "loader/model/objLoader.h"
#include "loader/model/objStructure.h"

OnStart OnMonkeyStart(GameObject* gameObject);


Mesh objToMesh(objModel model);