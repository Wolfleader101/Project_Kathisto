#include "Game.h"

void InitGameObjectManager(GameObjectManager* gameObjectManager)
{
	const size_t count = 20u;
	gameObjectManager->count = count;
	gameObjectManager->gameObjects = malloc(count * sizeof(GameObject));
	gameObjectManager->boundingBoxes = malloc(count * sizeof(BoudingBox));
	gameObjectManager->lastIndex = 0u;
	gameObjectManager->freeSpace = count;

	if (gameObjectManager->gameObjects == NULL) return;
	for (size_t i = 0; i < count; i++)
	{
		gameObjectManager->gameObjects[i] = malloc(sizeof(GameObject));
		if (gameObjectManager->gameObjects[i] == NULL) return;
		InitGameObject(gameObjectManager->gameObjects[i]);
	}
}

// TODO FIX THIS METHOD??
void GameObjectManagerIncrease(GameObjectManager* gameObjectManager)
{
	const size_t newCount = gameObjectManager->count + (gameObjectManager->count / 2);
	GameObject* temp = realloc(gameObjectManager->gameObjects, newCount * sizeof(GameObject));
	if (temp)
	{
		gameObjectManager->gameObjects = temp;

		for (size_t i = gameObjectManager->count; i < newCount; i++)
		{
			gameObjectManager->gameObjects[i] = malloc(sizeof(GameObject));
			if (gameObjectManager->gameObjects[i] == NULL) return;
			InitGameObject(gameObjectManager->gameObjects[i]);
		}

		gameObjectManager->count += newCount;
		gameObjectManager->freeSpace += newCount;
	}
}

/*
When a GameObject is added:
	add the game object to the end of the game object list at index of count using realloc
	increase count by 1
 */
void GameObjectManagerAdd(GameObjectManager* gameObjectManager, GameObject* gameObject)
{
	if (gameObjectManager->freeSpace == 0)
		GameObjectManagerIncrease(gameObjectManager);

	// set its id to the last index
	gameObject->id = gameObjectManager->lastIndex;

	// set the bounding box
	gameObject->rigidBody.boundingBox.gameObjectId = gameObjectManager->lastIndex;


	// add the address of the bounding box to the array
	gameObjectManager->boundingBoxes[gameObjectManager->lastIndex] = &gameObject->rigidBody.boundingBox;

	// set the last index to the game object to be added
	gameObjectManager->gameObjects[gameObjectManager->lastIndex] = gameObject;

	// then call the on start method
	// NOTE THE ONSTART SHOULD NEVER BE NULL, IF ITS NULL THEN YOU HAVE DONE SOMETHING WRONG, THATS WHY THE IF STATEMENT IS COMMENTED OUT
	//if (gameObjectManager->gameObjects[gameObjectManager->lastIndex].OnStart != NULL)
	gameObjectManager->gameObjects[gameObjectManager->lastIndex]->OnStart(gameObjectManager->gameObjects[gameObjectManager->lastIndex]);


	// calculate bounding box
	CalculateBoundingBox(gameObject);

	gameObjectManager->freeSpace--;
	gameObjectManager->lastIndex++;
}

/*
When a GameObject is removed:
	remove the gameobject from the game object list by setting by freeing it
	for all gameobjects where index > deleted index
	copy the gameobject over to gameobject[i - 1]
	take 1 from count
	freespace add 1
	lastIndex take 1
 */
void GameObjectManagerRemove(GameObjectManager* gameObjectManager, size_t id)
{
	FreeGameObject(gameObjectManager->gameObjects[id]);
	if (gameObjectManager->gameObjects[id] == NULL) return;
	for (size_t i = id + 1; i < gameObjectManager->count; i++)
	{
		// move the game object pointers
		gameObjectManager->gameObjects[i - 1] = gameObjectManager->gameObjects[i];
		gameObjectManager->gameObjects[i - 1]->id = i - 1;

		// move the bounding box pointers
		gameObjectManager->boundingBoxes[i - 1] = gameObjectManager->boundingBoxes[i];
		// TODO FIX THIS ERORR???
		gameObjectManager->boundingBoxes[i - 1]->gameObjectId = i - 1;

		// free the last object
		if (i == gameObjectManager->count - 1)
			FreeGameObject(gameObjectManager->gameObjects[i]);
	}

	gameObjectManager->count--;
	gameObjectManager->freeSpace++;
	gameObjectManager->lastIndex--;
}

GameObject* GameObjectManagerFind(GameObjectManager* gameObjectManager, size_t id)
{
	return gameObjectManager->gameObjects[id];
}

void UpdateGameObjects(Time time, GameObjectManager* gameObjectManager)
{
	for (size_t i = 0; i < gameObjectManager->lastIndex; i++)
	{
		UpdateGameObject(time, gameObjectManager->gameObjects[i]);
	}
}

void InitGameObject(GameObject* gameObject)
{
	gameObject->id = 0;
	gameObject->name = NULL;
	InitTransform(&gameObject->transform);
	InitMesh(&gameObject->mesh);
	InitRigidBody(&gameObject->rigidBody);
	gameObject->debug = false;
	gameObject->OnStart = NULL;
	gameObject->OnUpdate = NULL;
	gameObject->OnFixedUpdate = NULL;
}

void SetupCallbacks(GameObject* gameObject, OnStart OnStart, OnUpdate OnUpdate, OnLateUpdate OnLateUpdate, OnFixedUpdate OnFixedUpdate)
{
	gameObject->OnStart = OnStart;
	gameObject->OnUpdate = OnUpdate;
	gameObject->OnLateUpdate = OnLateUpdate;
	gameObject->OnFixedUpdate = OnFixedUpdate;
}

void UpdateGameObject(Time time, GameObject* gameObject)
{
	glPushMatrix();

	if (gameObject->OnUpdate != NULL) gameObject->OnUpdate(time, gameObject);

	Mesh* mesh = &gameObject->mesh;

	UpdateTransform(time, &gameObject->transform);

	if (!gameObject->mesh.disableMesh)
		UpdateMesh(time, mesh);

	if (gameObject->debug)
		DrawGizmos(time, gameObject->rigidBody.boundingBox.maxPos);

	if (gameObject->OnLateUpdate != NULL) gameObject->OnLateUpdate(time, gameObject);

	glPopMatrix();

	if (gameObject->rigidBody.debug)
		DrawBoundingBox(gameObject->rigidBody.boundingBox);
}

void UpdateTransform(Time time, Transform* transform)
{
	Vector3* pos = &transform->position;
	Vector3* rot = &transform->rotation;
	Vector3* scale = &transform->scale;

	glTranslatef(pos->x, pos->y, pos->z);

	glRotatef(rot->x, 1.0f, 0.0f, 0.0f);
	glRotatef(rot->y, 0.0f, 1.0f, 0.0f);
	glRotatef(rot->z, 0.0f, 0.0f, 1.0f);

	glScalef(scale->x, scale->y, scale->z);
}

void UpdateMesh(Time time, Mesh* mesh)
{
	if (!mesh->isUniformColor) glEnableClientState(GL_COLOR_ARRAY);

	if (mesh->isUniformColor)
		glColor4f(mesh->colors[0].r, mesh->colors[0].g, mesh->colors[0].b, mesh->colors[0].a);
	else
		glColorPointer(4, GL_FLOAT, 4, mesh->colors);

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, mesh->points);

	glDrawElements(mesh->debug ? GL_LINE_LOOP : GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, mesh->indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	if (!mesh->isUniformColor) glDisableClientState(GL_COLOR_ARRAY);
}

void DrawGizmos(Time time, Vector3 maxSize)
{
	Vector3 gizmoSize = Vec3ScalarAdd(maxSize, 1.5f);

	// X
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gizmoSize.x, 0.0f, 0.0f);
	glEnd();

	// Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, gizmoSize.y, 0.0f);
	glEnd();

	// Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, gizmoSize.z);
	glEnd();
}

void FixedUpdateGameObjects(Time fixedTime, GameObjectManager* gameObjectManager)
{
	for (size_t i = 0; i < gameObjectManager->lastIndex; i++)
	{
		FixedUpdateGameObject(fixedTime, gameObjectManager, gameObjectManager->gameObjects[i]);
	}
}

void FixedUpdateGameObject(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject)
{
	// push a matrix so u dont modify the root matrix
	glPushMatrix();

	//Check for gravity enabled
	if (gameObject->rigidBody.useGravity && !gameObject->rigidBody.isStatic)
	{
		//Apply transformation
		GravityTransform(fixedTime, gameObject);
	}

	if(!gameObject->rigidBody.isStatic) CalculateBoundingBox(gameObject);
	if (!gameObject->rigidBody.isStatic) DetectCollision(fixedTime, gameObjectManager, gameObject);

	if (gameObject->OnFixedUpdate != NULL) gameObject->OnFixedUpdate(fixedTime, gameObject);

	float coefficentDrag = 1.05;

	float cubeWidth = gameObject->rigidBody.boundingBox.maxPos.x - gameObject->rigidBody.boundingBox.minPos.x;
	float cubeHeight = gameObject->rigidBody.boundingBox.maxPos.y - gameObject->rigidBody.boundingBox.minPos.y;
	float area = cubeWidth * cubeHeight;

	float drag = 5.0f;// 0.5f * AIR_DENSITY * (gameObject->rigidBody.velocity.x * gameObject->rigidBody.velocity.x) * area * coefficentDrag;

	if (abs(gameObject->rigidBody.velocity.x) > 0.0f)
		gameObject->rigidBody.velocity.x -= drag * fixedTime.deltaTime;

	if (abs(gameObject->rigidBody.velocity.z) > 0.0f)
		gameObject->rigidBody.velocity.z -= drag * fixedTime.deltaTime;

	gameObject->transform.position.x += gameObject->rigidBody.velocity.x * fixedTime.deltaTime;
	gameObject->transform.position.y += gameObject->rigidBody.velocity.y * fixedTime.deltaTime;
	gameObject->transform.position.z += gameObject->rigidBody.velocity.z * fixedTime.deltaTime;

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
		area = PI * rb->sphereBody.radius;
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

	if (abs(gameObject->rigidBody.velocity.y) > terminalVelocity) gameObject->rigidBody.velocity.y = -terminalVelocity;
}

void DrawBoundingBox(BoudingBox box)
{
	glPushMatrix();
	const Vector3 boundBoxVertexBuffer[] =
	{
	box.minPos,
	{ box.maxPos.x, box.minPos.y, box.minPos.z },
	{ box.minPos.x, box.maxPos.y, box.minPos.z },
	{ box.maxPos.x, box.maxPos.y, box.minPos.z },


	box.maxPos,
	{ box.maxPos.x, box.minPos.y, box.maxPos.z },
	{ box.minPos.x, box.maxPos.y, box.maxPos.z },
	{ box.minPos.x, box.minPos.y,  box.maxPos.z },
	};

	glColor3f(1.0f, 0.0f, 0.9f);

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, boundBoxVertexBuffer);

	glDrawElements(GL_LINE_LOOP, 36, GL_UNSIGNED_INT, cubeIndexBuffer);

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}

void CalculateBoundingBox(GameObject* gameObject)
{
	if (gameObject->mesh.points == NULL || gameObject->mesh.pointSize == 0) return;

	Transform* transform = &gameObject->transform;
	Mesh* mesh = &gameObject->mesh;

	Vector3 min = Vec3Multiply(transform->scale, mesh->points[0]);
	min = Vec3RotateZ(min, transform->rotation.z * PI / 180);
	min = Vec3RotateY(min, transform->rotation.y * PI / 180);
	min = Vec3RotateX(min, transform->rotation.x * PI / 180);


	min = Vec3Add(transform->position, min);

	Vector3 max = min;

	for (size_t i = 0; i < mesh->pointSize; i++)
	{
		Vector3 pos = Vec3Multiply(transform->scale, mesh->points[i]);
		pos = Vec3RotateZ(pos, transform->rotation.z * PI / 180);
		pos = Vec3RotateY(pos, transform->rotation.y * PI / 180);
		pos = Vec3RotateX(pos, transform->rotation.x * PI / 180);

		pos = Vec3Add(transform->position, pos);

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

void SphereResolution(Time fixedTime, GameObject* gameObject, GameObject* collidingObject)
{
	Vector3 normal = Vec3Normalize(collidingObject->transform.position);


	float dotDirNormal = Vec3DotProduct(gameObject->rigidBody.velocity, normal);
	Vector3 MulDotPlane = Vec3ScalarMultiply(normal, dotDirNormal);
	Vector3 ScalarByTwo = Vec3ScalarMultiply(MulDotPlane, 2);
	Vector3 newDir = Vec3Subtract(gameObject->rigidBody.velocity, ScalarByTwo);

	gameObject->rigidBody.velocity = newDir;

	Vector3 normalNewDir = Vec3Normalize(newDir);



	// half the boxes height,width,length
	float leftAmount = (gameObject->rigidBody.boundingBox.maxPos.x - gameObject->rigidBody.boundingBox.minPos.x);
	float upAmount = (gameObject->rigidBody.boundingBox.maxPos.y - gameObject->rigidBody.boundingBox.minPos.y);
	float forwardAmount = (gameObject->rigidBody.boundingBox.maxPos.z - gameObject->rigidBody.boundingBox.minPos.z);
	if (normalNewDir.x == 1.0f) gameObject->transform.position.x = collidingObject->rigidBody.boundingBox.maxPos.x + (leftAmount / 2);
	if (normalNewDir.y == 1.0f) gameObject->transform.position.y = collidingObject->rigidBody.boundingBox.maxPos.y + (upAmount / 2);
	if (normalNewDir.z == 1.0f) gameObject->transform.position.z = collidingObject->rigidBody.boundingBox.maxPos.z + (forwardAmount / 2);
	// decay = max of 75% decay or (multiplying velocity by .25), (mass * 1.5) / 100
	float decay = 1 - fminf((gameObject->rigidBody.mass * 1.5f) / 100, 0.75);

	if (!collidingObject->rigidBody.isStatic)
	{

		if (normalNewDir.x == 1.0f) collidingObject->transform.position.x = gameObject->rigidBody.boundingBox.maxPos.x + (leftAmount / 2);
		if (normalNewDir.y == 1.0f) collidingObject->transform.position.y = gameObject->rigidBody.boundingBox.maxPos.y + (upAmount / 2);
		if (normalNewDir.z == 1.0f) collidingObject->transform.position.z = gameObject->rigidBody.boundingBox.maxPos.z + (forwardAmount / 2);



		// transfer half of the decay to the gameobject
		// add velocity to it
		// e.g
		// .25( decay) * mass = veloicty
		if (newDir.x == 0 && newDir.y == 0 && newDir.z == 0) return;

		Vector3 newVel = Vec3ScalarMultiply(Vec3ScalarMultiply(normalNewDir, (decay * collidingObject->rigidBody.mass) / 2), -1.0f);
		collidingObject->rigidBody.velocity = newVel;
	}

	// if velocity is less than or equal to if its on the floor, stop
	//if (Vec3Length(gameObject->rigidBody.velocity) <= 0.7f) return;


	//gameObject->rigidBody.velocity = Vec3Multiply(gameObject->rigidBody.velocity, Vec3ScalarMultiply(normalNewDir, decay));
	if (normalNewDir.x == 1.0f) gameObject->rigidBody.velocity.x *= decay;
	if (normalNewDir.y == 1.0f) gameObject->rigidBody.velocity.y *= decay;
	if (normalNewDir.z == 1.0f) gameObject->rigidBody.velocity.z *= decay;



}

void DetectCollision(Time fixedTime, GameObjectManager* gameObjectManager, GameObject* gameObject)
{
	if (gameObject->rigidBody.sphereBody.isSphere)
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
					//SphereResolution(fixedTime, gameObject);
				}
			}
			else
			{
				BoudingBox* box = &gameObjectManager->boundingBoxes[i];
				// do plane collision detection
				float cx = fmaxf(box->minPos.x, fminf(gameObject->transform.position.x, box->maxPos.x));
				float cy = fmaxf(box->minPos.y, fminf(gameObject->transform.position.y, box->maxPos.y));
				float cz = fmaxf(box->minPos.z, fminf(gameObject->transform.position.z, box->maxPos.z));

				double px = pow((double)cx - gameObject->transform.position.x, 2);
				double py = pow((double)cy - gameObject->transform.position.y, 2);
				double pz = pow((double)cz - gameObject->transform.position.z, 2);
				float distance = sqrt(px + py + pz);

				if (distance < gameObject->rigidBody.sphereBody.radius)
				{
					// colliding with
					SphereResolution(fixedTime, gameObject, box);
					return;
				}
			}
		}
	}

	BoudingBox* objBox = &gameObject->rigidBody.boundingBox;
	for (size_t i = 0; i < gameObjectManager->lastIndex; ++i)
	{
		if (gameObjectManager->boundingBoxes[i]->gameObjectId == gameObject->id) continue;

		BoudingBox* checkgBox = gameObjectManager->boundingBoxes[i];
		bool xCollision = objBox->minPos.x <= checkgBox->maxPos.x && objBox->maxPos.x >= checkgBox->minPos.x;
		bool yCollision = objBox->minPos.y <= checkgBox->maxPos.y && objBox->maxPos.y >= checkgBox->minPos.y;
		bool zCollision = objBox->minPos.z <= checkgBox->maxPos.z && objBox->maxPos.z >= checkgBox->minPos.z;
		if (xCollision && yCollision && zCollision)
		{
			//printf("%s is inside of %s\n", gameObject->name, gameObjectManager->gameObjects[checkgBox->gameObjectId]->name);

			SphereResolution(fixedTime, gameObject, gameObjectManager->gameObjects[i]);
			return;
		}
	}
}


void FreeGameObject(GameObject* gameObject)
{
	//free(gameObject->name);
	free(gameObject);
	gameObject = NULL;
}

void InitTransform(Transform* transform)
{
	transform->position = EmptyVec3();
	transform->rotation = EmptyVec3();
	transform->scale = (Vector3){ 1.0f, 1.0f, 1.0f };
}

void InitMesh(Mesh* mesh)
{
	mesh->points = NULL;
	mesh->indices = NULL;
	mesh->indexCount = 0;
	mesh->colors = NULL;
	mesh->isUniformColor = false;
	mesh->debug = false;
	mesh->disableMesh = false;
}

void InitRigidBody(RigidBody* rigidBody)
{
	rigidBody->isStatic = false;
	rigidBody->useGravity = false;
	rigidBody->debug = false;
	rigidBody->mass = 50.0f;
	rigidBody->velocity = EmptyVec3();
	rigidBody->boundingBox = (BoudingBox){ .gameObjectId = 0, .minPos = EmptyVec3(), .maxPos = EmptyVec3() };
	rigidBody->sphereBody = (SphereBody){ .isSphere = false, .radius = 0.0f };
}
