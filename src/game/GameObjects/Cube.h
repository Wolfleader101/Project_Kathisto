#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"


#include "loader/model/objLoader.h"
#include "loader/model/objStructure.h"

#include "math/mathUtils.h"
#include "game/Rendering.h"
#include "game/GameConstants.h"




OnStart OnCubeStart(GameObject* gameObject);

OnUpdate OnCubeUpdate(Time time, GameObject* gameObject);
OnFixedUpdate OnCubeFixedUpdate(Time time, GameObject* gameObject);

OnCollision OnCubeCollision(Time time, GameObject* gameObject, GameObject* collisionObject);