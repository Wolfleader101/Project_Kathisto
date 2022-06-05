#pragma once

#include "utilities/vectorUtil.h"

typedef struct objModel
{
    unsigned nVerts;                    //Number of vertices in the model
    unsigned nUVs;                      //Number of UVs in the model
    unsigned nNormals;                  //Number of normals in the model
    unsigned nFaces;                    //Number of faces in the model

    listVec3 vertPosition;              //Stores the position of a vertex (v)
    listVec2 textureCoord;              //Stores the texture coordinate of each vertex (vt)
    listVec3 normalData;                //Stores the normals of each vertex (vn)

    listVec3Int vertexPosIndicies;      //Face indicies which represent the vertexes
    listVec3Int normalIndicies;         //Face indicies which represent the vertex normals
    listVec3Int textureCoordIndicies;   //Face indicies which represent the texture coordinares
} objModel;