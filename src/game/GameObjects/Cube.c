#include "Cube.h"

const RGBA cubeColorBuffer[] = {
	// front colors
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f},
	// back colors
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f}
};

OnStart OnCubeStart(GameObject* gameObject)
{
	gameObject->name = "Cube";

	//unsigned int texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//// set the texture wrapping/filtering options (on the currently bound texture object)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//int width, height, nrChannels;
	//unsigned char* data = stbi_load("assets/textures/container.jpg", &width, &height, &nrChannels, 0);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);

	//stbi_image_free(data);

	//glTexCoordPointer(2, GL_FLOAT, sizeof(Vector2), texture);


	gameObject->mesh = cubeMeshCustColours;

	LoadTexture("assets/textures/container.jpg", &gameObject->mesh.texture);

	gameObject->mesh.hasTexture = true;
	gameObject->transform.position = (Vector3){ 5.0f, 10.0f, 5.0f };
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f };
	gameObject->rigidBody.useGravity = true;
	gameObject->rigidBody.isStatic = false;
}

OnUpdate OnCubeUpdate(Time time, GameObject* gameObject)
{
	//Vector3* pos = &gameObject->transform.position;

	//float amplitude = 2.0f;
	//float period = 2.0f;

	//float theta = (time.currTime) * period;
	//float distance = sin(theta) / amplitude;

	//float hover = lerp(6.0f, 12.0f, distance);

	//pos->y = hover;


	//Vector3* rot = &gameObject->transform.rotation;
	//rot->x += (time.deltaTime * 20);
	//rot->y += (time.deltaTime * 20);
	//rot->z += (time.deltaTime * 20);


}

OnFixedUpdate OnCubeFixedUpdate(Time time, GameObject* gameObject)
{
}

OnCollision OnCubeCollision(Time time, GameObject* gameObject, GameObject* collisionObject) 
{

}