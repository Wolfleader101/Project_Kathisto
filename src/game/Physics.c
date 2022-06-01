#include "Physics.h"

void InitRigidBody(RigidBody* rigidBody)
{
	rigidBody->isStatic = false;
	rigidBody->isFloor = false;
	rigidBody->onGround = false;
	rigidBody->useGravity = false;
	rigidBody->debug = false;
	rigidBody->mass = 50.0f;
	rigidBody->velocity = EmptyVec3();
	rigidBody->boundingBox = (BoudingBox){ .gameObjectId = 0, .minPos = EmptyVec3(), .maxPos = EmptyVec3() };
	rigidBody->sphereBody = (SphereBody){ .isSphere = false, .radius = 0.0f };
}

void FixedUpdateGameObject(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject)
{
	// if the game object is static, it should not have physics
	if (gameObject->rigidBody.isStatic) return;

	// push a matrix so u dont modify the root matrix
	glPushMatrix();

	//Check for gravity enabled
	if (gameObject->rigidBody.useGravity)
	{
		//Apply gravity transformation
		GravityTransform(fixedTime, gameObject);
	}

	CollisionData collisionData = IsColliding(gameObjectManager, gameObject);
	// @Charlie On Collision should be here
	//IF collidingObject != NULL && gameObject->rigidBody.isTrigger && gameObject->rigidBody.OnCollision != NULL)  gameObject->rigidBody.OnCollision(fixedTime, gameObject, collidingObject);
	// also change below to (... && !gameObject->rigidBody.isTrigger) so that triggers dont move
	if (collisionData.collidingGameObject != NULL) CollisionResolution(fixedTime, gameObject, collisionData);

	if (collisionData.collidingGameObject == NULL && gameObject->rigidBody.onGround) gameObject->rigidBody.onGround = false;

	// apply friction and drag
	PhysicsTransform(fixedTime, gameObject, collisionData);

	if (gameObject->OnFixedUpdate != NULL) gameObject->OnFixedUpdate(fixedTime, gameObject);

	gameObject->transform.position.x += gameObject->rigidBody.velocity.x * fixedTime.deltaTime;
	gameObject->transform.position.y += gameObject->rigidBody.velocity.y * fixedTime.deltaTime;
	gameObject->transform.position.z += gameObject->rigidBody.velocity.z * fixedTime.deltaTime;

	// calculate the bounding box after transformations have been done so it doesn't sink into the ground
	CalculateBoundingBox(gameObject);

	glPopMatrix();
}

//Applies gravity transformation to object
void GravityTransform(Time fixedTime, GameObject* gameObject)
{
	RigidBody* rb = &gameObject->rigidBody;

	//Increase velocity of object by 9.81 m/s
	rb->velocity.y -= G_ACCELERATION * fixedTime.deltaTime;

	//Terminal velocity is based on a formaula of v_t
	// v_t = sqrt((2 * m * g)/(*p * A * Cd))

	// g = gravity acceleration in m/s^2
	// m = mass of object
	// p = density of fluid (in this case air)
	// A = cross sectional area in m^2
	// Cd = coefficient of drag


	// density of air 1.225kg/m^3
	// co efficent for streamline shape is smaller,
	// cube is 1.05
	// sphere is 0.47

	float area = 0.0f;
	float coefficentDrag = 0.0f;

	if (rb->sphereBody.isSphere)
	{
		// if sphere
		area = M_PI * rb->sphereBody.radius;
		coefficentDrag = 0.47;
	}
	else
	{
		// if cube
		float cubeWidth = rb->boundingBox.maxPos.x - rb->boundingBox.minPos.x;
		float cubeHeight = rb->boundingBox.maxPos.y - rb->boundingBox.minPos.y;
		area = cubeWidth * cubeHeight;
		coefficentDrag = 1.05;
	}


	float x = 2 * rb->mass * G_ACCELERATION;
	float y = AIR_DENSITY * area * coefficentDrag;
	float z = x / y;
	float terminalVelocity = sqrt(z);

	if (fabs(gameObject->rigidBody.velocity.y) > terminalVelocity) gameObject->rigidBody.velocity.y = -terminalVelocity;
}

void PhysicsTransform(Time fixedTime, GameObject* gameObject, CollisionData collisionData)
{
	RigidBody* rigidBody = &gameObject->rigidBody;

	// ground friction
	if (rigidBody->onGround && collisionData.collidingGameObject != NULL && collisionData.collidingGameObject->rigidBody.isFloor)
	{
		//https://sciencing.com/calculate-force-friction-6454395.html
		//https://www.omnicalculator.com/physics/friction

		float normalForce = rigidBody->mass * G_ACCELERATION * cos(collisionData.collidingGameObject->transform.rotation.z);
		// static coefficent of wood is 0.6 but wood sliding is .32
		float uSlide = 0.32f;
		float force = (uSlide * normalForce) * 0.25f;


		if (rigidBody->velocity.x >= -0.1f && rigidBody->velocity.x <= 0.1f)
		{
			rigidBody->velocity.x = 0.0f;
		}
		else if (rigidBody->velocity.x > 0.0f)
			rigidBody->velocity.x -= force * fixedTime.deltaTime;
		else if (rigidBody->velocity.x < 0.0f)
			rigidBody->velocity.x += force * fixedTime.deltaTime;

		if (rigidBody->velocity.z >= -0.1f && rigidBody->velocity.z <= 0.1f)
		{
			rigidBody->velocity.z = 0.0f;
		}
		else if (rigidBody->velocity.z > 0.0f)
			rigidBody->velocity.z -= force * fixedTime.deltaTime;
		else if (rigidBody->velocity.z < 0.0f)
			rigidBody->velocity.z += force * fixedTime.deltaTime;


		return;
	}

	// Air DRAG
	float coefficentDrag = 1.05;

	float cubeWidth = rigidBody->boundingBox.maxPos.x - rigidBody->boundingBox.minPos.x;
	float cubeHeight = rigidBody->boundingBox.maxPos.y - rigidBody->boundingBox.minPos.y;
	float area = cubeWidth * cubeHeight;

	float xdrag = 0.25f * AIR_DENSITY * gameObject->rigidBody.velocity.x * area * coefficentDrag;
	float zdrag = 0.25f * AIR_DENSITY * gameObject->rigidBody.velocity.z * area * coefficentDrag;


	if (rigidBody->velocity.x == 0.0f)
	{
	}
	else if (rigidBody->velocity.x > 0.0f)
		rigidBody->velocity.x -= xdrag * fixedTime.deltaTime;
	else if (rigidBody->velocity.x < 0.0f)
		rigidBody->velocity.x += xdrag * fixedTime.deltaTime;

	if (rigidBody->velocity.z == 0.0f)
	{
	}
	else if (rigidBody->velocity.z > 0.0f)
		rigidBody->velocity.z -= zdrag * fixedTime.deltaTime;
	else if (rigidBody->velocity.z < 0.0f)
		rigidBody->velocity.z += zdrag * fixedTime.deltaTime;

}

void CalculateBoundingBox(GameObject* gameObject)
{
	if (gameObject->mesh.points == NULL || gameObject->mesh.pointSize == 0) return;

	Transform* transform = &gameObject->transform;
	Mesh* mesh = &gameObject->mesh;

	Vector3 min;
	Vector3 max;

	for (size_t i = 0; i < mesh->pointSize; i++)
	{
		Vector3 pos = Vec3Multiply(transform->scale, mesh->points[i]);
		pos = Vec3RotateZ(pos, transform->rotation.z * M_PI / 180);
		pos = Vec3RotateY(pos, transform->rotation.y * M_PI / 180);
		pos = Vec3RotateX(pos, transform->rotation.x * M_PI / 180);
		pos = Vec3Add(transform->position, pos);

		if (i == 0) min = max = pos;

		if (pos.x < min.x) min.x = pos.x;
		if (pos.y < min.y) min.y = pos.y;
		if (pos.z < min.z) min.z = pos.z;

		if (pos.x > max.x) max.x = pos.x;
		if (pos.y > max.y) max.y = pos.y;
		if (pos.z > max.z) max.z = pos.z;
	}

	gameObject->rigidBody.boundingBox.minPos = min;
	gameObject->rigidBody.boundingBox.maxPos = max;
}

CollisionData IsColliding(GameObjectManager* gameObjectManager, GameObject* gameObject)
{
	if (gameObject->rigidBody.sphereBody.isSphere)
	{
		return SphereCollision(gameObjectManager, gameObject);
	}

	return BoxCollision(gameObjectManager, gameObject);
}

CollisionData SphereCollision(GameObjectManager* gameObjectManager, GameObject* gameObject)
{
	float radius = gameObject->rigidBody.sphereBody.radius;

	for (size_t i = 0; i < gameObjectManager->lastIndex; ++i)
	{
		if (gameObject->rigidBody.sphereBody.isSphere)
		{
			double dx = pow((double)gameObject->transform.position.x - gameObjectManager->gameObjects[i]->transform.position.x, 2);
			double dy = pow((double)gameObject->transform.position.y - gameObjectManager->gameObjects[i]->transform.position.y, 2);
			double dz = pow((double)gameObject->transform.position.z - gameObjectManager->gameObjects[i]->transform.position.z, 2);
			float distance = sqrt(dx + dy + dz);
			float radii = gameObject->rigidBody.sphereBody.radius
				+ gameObjectManager->gameObjects[i]->rigidBody.sphereBody.radius;
			if (distance <= radii)
			{
				// TODO FIX THIS
				return (CollisionData) { .collidingFace = 0, .collidingGameObject = gameObjectManager->gameObjects[i] };
			}
		}
		// do plane collision detection
		else
		{
			BoudingBox* box = &gameObjectManager->boundingBoxes[i];
			float cx = fmaxf(box->minPos.x, fminf(gameObject->transform.position.x, box->maxPos.x));
			float cy = fmaxf(box->minPos.y, fminf(gameObject->transform.position.y, box->maxPos.y));
			float cz = fmaxf(box->minPos.z, fminf(gameObject->transform.position.z, box->maxPos.z));

			double px = pow((double)cx - gameObject->transform.position.x, 2);
			double py = pow((double)cy - gameObject->transform.position.y, 2);
			double pz = pow((double)cz - gameObject->transform.position.z, 2);
			float distance = sqrt(px + py + pz);

			if (distance < gameObject->rigidBody.sphereBody.radius)
			{
				// TODO FIX THIS
				return (CollisionData) { .collidingFace = 0, .collidingGameObject = gameObjectManager->gameObjects[i] };
				//return gameObjectManager->gameObjects[i];
			}
		}
	}

	return (CollisionData) { .collidingFace = 0, .collidingGameObject = NULL };;
}

CollisionData BoxCollision(GameObjectManager* gameObjectManager, GameObject* gameObject)
{
	BoudingBox* objBox = &gameObject->rigidBody.boundingBox;
	for (size_t i = 0; i < gameObjectManager->lastIndex; ++i)
	{
		if (gameObjectManager->boundingBoxes[i] == NULL)
		{
			gameObjectManager->boundingBoxes[i] = &gameObjectManager->gameObjects[i]->rigidBody;
		}
		if (gameObjectManager->boundingBoxes[i]->gameObjectId == gameObject->id) continue;

		BoudingBox* checkgBox = gameObjectManager->boundingBoxes[i];
		bool xCollision = objBox->minPos.x <= checkgBox->maxPos.x && objBox->maxPos.x >= checkgBox->minPos.x;
		bool yCollision = objBox->minPos.y <= checkgBox->maxPos.y && objBox->maxPos.y >= checkgBox->minPos.y;
		bool zCollision = objBox->minPos.z <= checkgBox->maxPos.z && objBox->maxPos.z >= checkgBox->minPos.z;
		if (xCollision && yCollision && zCollision)
		{
			float max = -2.0f;
			size_t best_match = 0u;

			if (gameObjectManager->gameObjects[i]->rigidBody.isFloor)
			{
				return (CollisionData) { .collidingFace = (Vector3){ 0.0f, 1.0f, 0.0f }, .collidingGameObject = gameObjectManager->gameObjects[i] };
			}
			for (size_t j = 0; !gameObjectManager->gameObjects[i]->rigidBody.isFloor && j < VECTOR_DIRECTIONS_LENGTH; ++j)
			{
				float dot = Vec3DotProduct(VECTOR_DIRECTIONS[j], Vec3Normalize(
					Vec3Subtract(gameObject->transform.position, gameObjectManager->gameObjects[i]->transform.position)));

				if (dot > max)
				{
					max = dot;
					best_match = j;
				}
			}

			Vector3 collidingFace = VECTOR_DIRECTIONS[best_match];

			return (CollisionData) { .collidingFace = collidingFace, .collidingGameObject = gameObjectManager->gameObjects[i] };
		}
	}

	return (CollisionData) { .collidingFace = 0, .collidingGameObject = NULL };
}

void CollisionResolution(Time fixedTime, GameObject* gameObject, CollisionData collisionData)
{
	if (collisionData.collidingFace.y == 1.0f && collisionData.collidingGameObject->rigidBody.isFloor)
		gameObject->rigidBody.onGround = true;
	else
		gameObject->rigidBody.onGround = false;

	Vector3 normal = collisionData.collidingFace;
	//printf("GameObject: %s, Colliding Obj: %s, Normal: %.2f %.2f %.2f\n", gameObject->name, collisionData.collidingGameObject->name, normal.x, normal.y, normal.z);

	float dotDirNormal = Vec3DotProduct(gameObject->rigidBody.velocity, normal);
	Vector3 MulDotPlane = Vec3ScalarMultiply(normal, dotDirNormal);
	Vector3 ScalarByTwo = Vec3ScalarMultiply(MulDotPlane, 2);
	Vector3 newDir = Vec3Subtract(gameObject->rigidBody.velocity, ScalarByTwo);

	printf("Velocity: %.2f %.2f %.2f\n", gameObject->rigidBody.velocity.x, gameObject->rigidBody.velocity.y, gameObject->rigidBody.velocity.z);
	gameObject->rigidBody.velocity = newDir;
	printf("GameObject: %s, Colliding Obj: %s, Velocity: %.2f %.2f %.2f\n", gameObject->name, collisionData.collidingGameObject->name, newDir.x, newDir.y, newDir.z);

	// decay = max of 75% decay or (multiplying velocity by .25), (mass * 1.5) / 100
	float decay = 1 - fminf((gameObject->rigidBody.mass * 1.5f) / 100, 0.75);

	Vector3 normalNewDir = Vec3Normalize(newDir);


	//look into on ground collision??

	float upAmount = (gameObject->rigidBody.boundingBox.maxPos.y - gameObject->rigidBody.boundingBox.minPos.y);
	if (normalNewDir.y == 1.0f && collisionData.collidingGameObject->rigidBody.isFloor)
		gameObject->transform.position.y = collisionData.collidingGameObject->rigidBody.boundingBox.maxPos.y + (upAmount / 2);

	float rightAmount = (gameObject->rigidBody.boundingBox.maxPos.x - gameObject->rigidBody.boundingBox.minPos.x);
	if (normalNewDir.x == 1.0f)
		gameObject->transform.position.x = collisionData.collidingGameObject->rigidBody.boundingBox.maxPos.x + (rightAmount / 2);

	float forwardAmount = (gameObject->rigidBody.boundingBox.maxPos.z - gameObject->rigidBody.boundingBox.minPos.z);
	if (normalNewDir.z == 1.0f)
		gameObject->transform.position.z = collisionData.collidingGameObject->rigidBody.boundingBox.maxPos.z + (forwardAmount / 2);

	// if colliding game object is static or on ground, do not move it
	if (!collisionData.collidingGameObject->rigidBody.isStatic && !collisionData.collidingGameObject->rigidBody.onGround)
	{
		// transfer a % of the decay to the gameobject
		// .25( decay) * mass / 2 = veloicty
		if (newDir.x == 0 && newDir.y == 0 && newDir.z == 0) return;

		Vector3 newVel = Vec3ScalarMultiply(Vec3ScalarMultiply(normalNewDir, (decay * collisionData.collidingGameObject->rigidBody.mass) / 2), -1.0f);
		collisionData.collidingGameObject->rigidBody.velocity = newVel;
	}

	if (normalNewDir.x > 0.0f) gameObject->rigidBody.velocity.x *= decay;
	if (normalNewDir.y > 0.0f) gameObject->rigidBody.velocity.y *= decay;
	if (normalNewDir.z > 0.0f) gameObject->rigidBody.velocity.z *= decay;

}