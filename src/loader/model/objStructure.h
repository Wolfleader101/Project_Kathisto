#pragma once

#include "math/Vector.h"

/**
 * @struct An OBJ File's Data
 * @brief A structure to hold all of the data of an OBJ File
*/
typedef struct ObjModel
{
    /**
     * @brief The name of the OBJ Group
     */
    char* modelName;                    //The name of the model

    /**
     * @brief The number of verticies in the group
     */
    unsigned nVerts;                    //Number of vertices in the model
    /**
     * @brief The number of uvs in the group
     */
    unsigned nUVs;                      //Number of UVs in the model
    /**
     * @brief The number of normals in the group
     */
    unsigned nNormals;                  //Number of normals in the model
    /**
     * @brief The number of faces in the group
     */
    unsigned nFaces;                    //Number of faces in the model

    /**
     * @brief The vertexes in the group
     */
    Vector3* vertPosition;              //Stores the position of a vertex (v)
    /**
     * @brief The uvs in the group
     */
    Vector2* textureCoord;              //Stores the texture coordinate of each vertex (vt)
    /**
     * @brief The normals in the group
     */
    Vector3* normalData;                //Stores the normals of each vertex (vn)

    /**
     * @brief The vertex indexes in the group
     */
    Vector3Int* vertexPosIndicies;      //Face indicies which represent the vertexes
    /**
     * @brief The normal indexes in the group
     */
    Vector3Int* normalIndicies;         //Face indicies which represent the vertex normals
    /**
     * @brief The uv indexes in the group
     */
    Vector3Int* textureCoordIndicies;   //Face indicies which represent the texture coordinares
} ObjModel;

/**
 * @struct An OBJ File's Container
 * @brief A structure to hold all of the elements of an OBJ File
*/
typedef struct ObjFile
{
    /**
     * @brief The name of the OBJ File
     */
    char* fileName;                    //The name of the model
    /**
     * @brief The number of groups in the model
     */
    unsigned nGroups;                   //Number of groups in the model
    /**
     * @brief Individual OBJ Group Data
     */
    ObjModel* modelGroups;              //The individual models within a mode
} ObjFile;


/////////////////////////////////////////////////
//  EXAMPLES
//  
//  f 1437/2412/4159 1433/2399/4158 1435/2402/4160
//      - Triangulated Face = Vertex Point/Vertex Texture Coordinate/Vertex Normal
//      - f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
/////////////////////////////////////////////////