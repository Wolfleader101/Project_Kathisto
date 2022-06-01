#pragma once

#include "game/GameIncludes.h"
#include "game/GameTypes.h"
#include "game/GameObjectManager.h"

extern const RGBA Teleporter1ColorBuffer[1];
extern const RGBA Teleporter2ColorBuffer[1];

extern bool areTeleportersReady;
extern const float maxTeleCooldown;
extern float teleCooldown;

OnStart OnTeleporter1Start(GameObject* gameObject);
OnStart OnTeleporter2Start(GameObject* gameObject);

OnCollision OnTeleporter1Collision(Time time, GameObject* gameObject, GameObject* collisionObject);
OnCollision OnTeleporter2Collision(Time time, GameObject* gameObject, GameObject* collisionObject);

OnUpdate OnTeleporter1Update(Time time, GameObject* gameObject);
