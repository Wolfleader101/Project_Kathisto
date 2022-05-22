#include "Game.h"

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
		DrawMesh(time, mesh);

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
