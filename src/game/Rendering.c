#include "Rendering.h"

void DrawMesh(Time time, Mesh* mesh)
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
