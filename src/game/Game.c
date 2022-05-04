#include "Game.h"
#include "GameConstants.h"

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

/**
 * @brief
 * 	When a GameObject is added:
		add the game object to the end of the game object list at index of count using realloc
		increase count by 1
 * @param gameObjectManager
 * @param gameObject
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

	gameObjectManager->freeSpace--;
	gameObjectManager->lastIndex++;
}

/**
 * @brief
 * When a GameObject is removed:
		remove the gameobject from the game object list by setting by freeing it
		for all gameobjects where index > deleted index
		copy the gameobject over to gameobject[i - 1]
		take 1 from count
		freespace add 1
		lastIndex take 1
 * @param gameObjectManager
 * @param id
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

	UpdateMesh(time, mesh);

	if (gameObject->debug)
		DrawGizmos(time, gameObject->rigidBody.boundingBox.maxPos);


	if (gameObject->OnLateUpdate != NULL) gameObject->OnLateUpdate(time, gameObject);

	glPopMatrix();
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

	CalculateBoundingBox(gameObject);
	if(!gameObject->rigidBody.isStatic) DetectCollision(gameObjectManager, gameObject);

	if (gameObject->OnFixedUpdate != NULL) gameObject->OnFixedUpdate(fixedTime, gameObject);

	glPopMatrix();
}

//Applies gravity transformation to object
void GravityTransform(Time fixedTime, GameObject* gameObject)
{
	//Increase velocity of object by 9.8 m/s
	//Terminal velocity is 53m/s in Earth atmosphere
	gameObject->rigidBody.velocity.y -= G_ACCELERATION * fixedTime.deltaTime;
	if (abs(gameObject->rigidBody.velocity.y) > T_VELOCITY) gameObject->rigidBody.velocity.y = -T_VELOCITY;

	//Subtract object's Y transform position by velocity per second
	gameObject->transform.position.y += gameObject->rigidBody.velocity.y * fixedTime.deltaTime;

	//Resetting velocity must be done in collision resolution
}

void CalculateBoundingBox(GameObject* gameObject)
{
	if (gameObject->mesh.points == NULL || gameObject->mesh.pointSize == 0) return;

	Transform* transform = &gameObject->transform;
	Mesh* mesh = &gameObject->mesh;

	Vector3 min = Vec3Multiply(transform->scale, mesh->points[0]);
	min = Vec3RotateX(min, transform->rotation.x);
	min = Vec3RotateY(min, transform->rotation.y);
	min = Vec3RotateZ(min, transform->rotation.z);
	min = Vec3Add(transform->position, min);
	Vector3 max = min;

	for (size_t i = 0; i < mesh->pointSize; i++)
	{
		Vector3 pos = Vec3Multiply(transform->scale, mesh->points[i]);
		pos = Vec3RotateX(pos, transform->rotation.x);
		pos = Vec3RotateY(pos, transform->rotation.y);
		pos = Vec3RotateZ(pos, transform->rotation.z);
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

void DetectCollision(GameObjectManager* gameObjectManager, GameObject* gameObject)
{
	BoudingBox* objBox = &gameObject->rigidBody.boundingBox;
	for (size_t i = 0; i < gameObjectManager->lastIndex; i++)
	{
		if (gameObjectManager->boundingBoxes[i]->gameObjectId == gameObject->id) continue;

		BoudingBox* checkgBox = gameObjectManager->boundingBoxes[i];
		if ((objBox->minPos.x <= checkgBox->maxPos.x && objBox->maxPos.x >= checkgBox->minPos.x) &&
			(objBox->minPos.y <= checkgBox->maxPos.y && objBox->maxPos.y >= checkgBox->minPos.y) &&
			(objBox->minPos.z <= checkgBox->maxPos.z && objBox->maxPos.z >= checkgBox->minPos.z))
		{
			// get the cross product where the intersection is happening
			// then inverse the vectors direction, and then apply the velocity to that
			//Vector3 intersection = Vec3CrossProduct(objBox, )
			printf("%s is inside of %s\n", gameObject->name, gameObjectManager->gameObjects[checkgBox->gameObjectId]->name);
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
}

void InitRigidBody(RigidBody* rigidBody)
{
	rigidBody->isStatic = false;
	rigidBody->useGravity = false;
	rigidBody->mass = 0.0f;
	rigidBody->velocity = EmptyVec3();
	rigidBody->boundingBox = (BoudingBox){ .gameObjectId = 0, .minPos = EmptyVec3(), .maxPos = EmptyVec3() };
}

void SimulateRigidBody(RigidBody* RigidBody)
{

}
