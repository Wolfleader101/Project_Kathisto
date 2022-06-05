#include "Rendering.h"

void InitMesh(Mesh* mesh)
{
	mesh->points = NULL;
	mesh->pointSize = 0;
	mesh->indices = NULL;
	mesh->indexCount = 0;
	mesh->colors = NULL;
	mesh->isUniformColor = false;
	mesh->debug = false;
	mesh->disableMesh = false;

	InitTexture(&mesh->texture);
}

void InitTexture(Texture* texture)
{
	texture->id = 0u;
	texture->textureCoords = (Vector2*){ 0 };
	texture->width = 0;
	texture->height = 0;
	texture->channelsIn = 0;
	texture->desiredChannel = 0;
}

void LoadTexture(char* file, Texture* tex)
{
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tex->id);

	glBindTexture(GL_TEXTURE_2D, tex->id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//GL_LINEAR_MIPMAP_LINEAR
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// might need to create this into texture
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file, &tex->width, &tex->height, &tex->channelsIn, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, tex->width, tex->height, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	glDisable(GL_TEXTURE_2D);
}

void objToMesh(objModel model, Mesh* mesh)
{
	mesh->texture.textureCoords = model.textureCoord.vec2Items;
	mesh->points = model.vertPosition.vec3Items;
	mesh->indices = model.vertexPosIndicies.vec3IntItems;
	mesh->pointSize = model.nVerts;
	mesh->indexCount = (size_t)model.nFaces * 3;

	return mesh;
}

void DrawMesh(Time time, Mesh* mesh)
{
	if (mesh->hasTexture)
	{
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, mesh->texture.id);
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vector2), mesh->texture.textureCoords);

	}
	else {
		if (!mesh->isUniformColor) glEnableClientState(GL_COLOR_ARRAY);

		if (mesh->isUniformColor)
			glColor4fv(mesh->colors);
		else
			glColorPointer(4, GL_FLOAT, 4, mesh->colors);
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vector3), mesh->points);

	glDrawElements(mesh->debug ? GL_LINE_LOOP : GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, mesh->indices);

	glDisableClientState(GL_VERTEX_ARRAY);

	if (mesh->hasTexture)
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (!mesh->isUniformColor) glDisableClientState(GL_COLOR_ARRAY);
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
