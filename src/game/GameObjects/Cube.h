#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h"
#include "game/Game.h"
#include "math/mathUtils.h"


OnStart OnCubeStart(GameObject* gameObject);

OnUpdate OnCubeUpdate(Time time, GameObject* gameObject);
OnFixedUpdate OnCubeFixedUpdate(Time time, GameObject* gameObject);