#include "Game.h"

void drawMesh(Mesh mesh)
{
    if(!mesh.isUniformColor) glEnableClientState(GL_COLOR_ARRAY);

    if (mesh.isUniformColor) 
        glColor4f(mesh.colors[0].r, mesh.colors[0].g, mesh.colors[0].b, mesh.colors[0].a);
    else
        glColorPointer(4, GL_FLOAT, 4, mesh.colors);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, mesh.points);
    glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, mesh.indices);

    glDisableClientState(GL_VERTEX_ARRAY);
   if(!mesh.isUniformColor) glDisableClientState(GL_COLOR_ARRAY);
}
