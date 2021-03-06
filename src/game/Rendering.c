#include "Rendering.h"

void InitMesh(Mesh* mesh)
{
	mesh->points = NULL;
	mesh->vertexAmount = 0;
	mesh->uvs = NULL;
	mesh->uvAmount = 0;
	mesh->normals = NULL;
	mesh->normalAmount = 0;

	mesh->vertexIndices = NULL;
	mesh->uvIndices = NULL;
	mesh->normalIndices = NULL;

	mesh->indexCount = 0;

	mesh->colors = NULL;
	mesh->isUniformColor = false;

	mesh->hasMaterial = false;
	mesh->meshDiffuse = (GLColour){0.0, 0.0, 0.0, 0.0};
	mesh->meshAmbient = (GLColour){ 0.0, 0.0, 0.0, 0.0 };
	mesh->meshSpecular = (GLColour){ 0.0, 0.0, 0.0, 0.0 };
	mesh->meshShininess = (GLColour){ 0.0, 0.0, 0.0, 0.0 };

	mesh->debug = false;
	mesh->disableMesh = false;
}

void objToMesh(ObjModel model, Mesh* mesh)
{
	mesh->points = model.vertPosition;
	mesh->vertexAmount = model.nVerts;
	mesh->uvs = model.textureCoord;
	mesh->uvAmount = model.nUVs;
	mesh->normals = model.normalData;
	mesh->normalAmount = model.nNormals;

	mesh->vertexIndices = model.vertexPosIndicies;
	mesh->uvIndices = model.textureCoordIndicies;
	mesh->normalIndices = model.vertexPosIndicies;

	mesh->indexCount = (size_t)model.nFaces * 3;

	return mesh;
}

void DrawMesh(Time time, Mesh* mesh)
{
	if (!mesh->isUniformColor && mesh->colors != NULL) glEnableClientState(GL_COLOR_ARRAY);

	if (mesh->colors != NULL && mesh->isUniformColor)
		glColor4fv(mesh->colors);
	else if (mesh->colors != NULL)
		glColorPointer(4, GL_FLOAT, 4, mesh->colors);
	else
	{
		glColor4f(0.5f, 0.75f, 0.5f, 1.0f);
	}

	if (mesh->normalAmount > 0) glEnableClientState(GL_NORMAL_ARRAY); //If there are normals present

	if (mesh->normalAmount > 0) //If there are normals present, set the normal pointer
	{
		glNormalPointer(GL_FLOAT, sizeof(Vector3), mesh->normals);
	}

	if(!mesh->hasMaterial)
	{
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}
	else
	{
		glDisable(GL_COLOR_MATERIAL);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat[]) { mesh->meshDiffuse.r, mesh->meshDiffuse.g, mesh->meshDiffuse.b, mesh->meshDiffuse.a });
		glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat[]) { mesh->meshAmbient.r, mesh->meshAmbient.g, mesh->meshAmbient.b, mesh->meshAmbient.a });
		glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat[]) { mesh->meshSpecular.r, mesh->meshSpecular.g, mesh->meshSpecular.b, mesh->meshSpecular.a });
		glMaterialfv(GL_FRONT, GL_SHININESS, (GLfloat[]) { mesh->meshShininess.r, mesh->meshShininess.g, mesh->meshShininess.b, mesh->meshShininess.a });
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vector3), mesh->points);

	glDrawElements(mesh->debug ? GL_LINE_LOOP : GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, mesh->vertexIndices);

	glDisableClientState(GL_VERTEX_ARRAY);
	if (!mesh->isUniformColor && mesh->colors != NULL) glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
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
