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

void FixedUpdateGameObjects(Time time, GameObjectManager* gameObjectManager)
{
	for (size_t i = 0; i < gameObjectManager->lastIndex; i++)
	{
		FixedUpdateGameObject(time, gameObjectManager->gameObjects[i]);
	}
}

void FixedUpdateGameObject(Time time, GameObject* gameObject)
{
	// push a matrix so u dont modify the root matrix
	glPushMatrix();

	CalculateBoundingBox(gameObject);

	if (gameObject->OnFixedUpdate != NULL) gameObject->OnFixedUpdate(time, gameObject);

	glPopMatrix();
}

void CalculateBoundingBox(GameObject* gameObject)
{
	if (gameObject->mesh.points == NULL || gameObject->mesh.pointSize == 0) return;

	Vector3 min = gameObject->mesh.points[0];
	Vector3 max = gameObject->mesh.points[0];

	for (size_t i = 0; i < gameObject->mesh.pointSize; i++)
	{
		if (gameObject->mesh.points[i].x < min.x) min.x = gameObject->mesh.points[i].x;
		if (gameObject->mesh.points[i].y < min.y) min.y = gameObject->mesh.points[i].y;
		if (gameObject->mesh.points[i].z < min.z) min.z = gameObject->mesh.points[i].z;

		if (gameObject->mesh.points[i].x > max.x) max.x = gameObject->mesh.points[i].x;
		if (gameObject->mesh.points[i].y > max.y) max.y = gameObject->mesh.points[i].y;
		if (gameObject->mesh.points[i].z > max.z) max.z = gameObject->mesh.points[i].z;
	}

	gameObject->rigidBody.boundingBox.minPos = min;
	gameObject->rigidBody.boundingBox.maxPos = max;
}

//bool IsInside

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
	rigidBody->velocity = 0.0f;
	rigidBody->boundingBox = (BoudingBox){ .gameObjectId = 0, .minPos = EmptyVec3(), .maxPos = EmptyVec3() };
}

void SimulateRigidBody(RigidBody* RigidBody)
{

}