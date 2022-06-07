#pragma once

#include "math/Vector.h"

typedef struct ObjModel
{
    char* modelName;                    //The name of the model

    unsigned nVerts;                    //Number of vertices in the model
    unsigned nUVs;                      //Number of UVs in the model
    unsigned nNormals;                  //Number of normals in the model
    unsigned nFaces;                    //Number of faces in the model

    Vector3* vertPosition;              //Stores the position of a vertex (v)
    Vector2* textureCoord;              //Stores the texture coordinate of each vertex (vt)
    Vector3* normalData;                //Stores the normals of each vertex (vn)

    Vector3Int* vertexPosIndicies;      //Face indicies which represent the vertexes
    Vector3Int* normalIndicies;         //Face indicies which represent the vertex normals
    Vector3Int* textureCoordIndicies;   //Face indicies which represent the texture coordinares

} ObjModel;


typedef struct ObjFile
{
    char* fileName;                    //The name of the model
    unsigned nGroups;                   //Number of groups in the model
    ObjModel* modelGroups;              //The individual models within a mode
} ObjFile;


/////////////////////////////////////////////////
//  EXAMPLES
//  
//  f 1437/2412/4159 1433/2399/4158 1435/2402/4160
//      - Triangulated Face = Vertex Point/Vertex Texture Coordinate/Vertex Normal
//      - f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
/////////////////////////////////////////////////