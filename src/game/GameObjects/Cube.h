#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h"
#include "game/Game.h"
#include "math/mathUtils.h"
#include "game/GameConstants.h"

OnStart OnCubeStart(GameObject* gameObject);

OnUpdate OnCubeUpdate(Time time, GameObject* gameObject);
OnFixedUpdate OnCubeFixedUpdate(Time time, GameObject* gameObject);

OnCollision OnCubeCollision(Time time, GameObject* gameObject, GameObject* collisionObject);