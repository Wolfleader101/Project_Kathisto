#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"

#include "math/mathUtils.h"
#include "game/GameConstants.h"


//isReady performs 'cooldown' for jump pad applying the jump boost
extern bool isReady;
extern float cooldown;
extern GameObject* collidingObject;

extern const RGBA JumpPadColorBuffer[1];

OnStart OnJumpPadStart(GameObject* gameObject);

OnUpdate OnJumpPadUpdate(Time time, GameObject* gameObject);
OnFixedUpdate OnJumpPadFixedUpdate(Time time, GameObject* gameObject);

OnCollision OnJumpPadCollision(Time time, GameObject* gameObject, GameObject* collisionObject);