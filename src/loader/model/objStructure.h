//////////////////////////////////////////////////////////////////////
//  OBJ FILE STRUCTURE
//
//  Data Structures used to hold OBJ data (BASIC REPRESENTATION)
//
//  Created by Darcy Lyndon Cukrov Wilson - 13/04/2022
//////////////////////////////////////////////////////////////////////

#include "math/Vector.h"

typedef struct objGroup
{
    char* groupName;                    //The name of the model group
    
    unsigned nVerts;                    //Number of vertices in the model (FOR AN INDIVIDUAL GROUP)
    unsigned nUVs;                      //Number of UVs in the model (FOR AN INDIVIDUAL GROUP)
    unsigned nNormals;                  //Number of normals in the model (FOR AN INDIVIDUAL GROUP)
    unsigned nFaces;                    //Number of faces in the model (FOR AN INDIVIDUAL GROUP)

    Vector3* vertPosition;              //Stores the position of a vertex (v) (FOR AN INDIVIDUAL GROUP)
    Vector2* textureCoord;              //Stores the texture coordinate of each vertex (vt) (FOR AN INDIVIDUAL GROUP)
    Vector3* normalData;                //Stores the normals of each vertex (vn) (FOR AN INDIVIDUAL GROUP)

    Vector3Int* grpVertexIndicies;      //Face indicies which represent the vertexes (FOR AN INDIVIDUAL GROUP)
    Vector3Int* grpNormalIndicies;      //Face indicies which represent the vertex normals (FOR AN INDIVIDUAL GROUP)
    Vector3Int* grpUVIndicies;          //Face indicies which represent the texture coordinares (FOR AN INDIVIDUAL GROUP)
} objGroup;

typedef struct objModel
{
    char* modelName;                    //The name of the model

    unsigned nVerts;                    //Number of vertices in the model
    unsigned nUVs;                      //Number of UVs in the model
    unsigned nNormals;                  //Number of normals in the model
    unsigned nFaces;                    //Number of faces in the model
    unsigned nGroups;                   //Number of groups in the model (Increased ONLY if there are groups present)

    Vector3* vertPosition;              //Stores the position of a vertex (v)
    Vector2* textureCoord;              //Stores the texture coordinate of each vertex (vt)
    Vector3* normalData;                //Stores the normals of each vertex (vn)

    Vector3Int* vertexPosIndicies;      //Face indicies which represent the vertexes
    Vector3Int* normalIndicies;         //Face indicies which represent the vertex normals
    Vector3Int* textureCoordIndicies;   //Face indicies which represent the texture coordinares

    objGroup* modelGroups;              //The individual groups within a model (Only used if nGroups is geater than 0, otherwise, must be set to NULL)
} objModel;

/////////////////////////////////////////////////
//  EXAMPLES
//  
//  f 1437/2412/4159 1433/2399/4158 1435/2402/4160
//      - Triangulated Face = Vertex Point/Vertex Texture Coordinate/Vertex Normal
//      - f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//  REFERENCES
/////////////////////////////////////////////////

// https://www.loc.gov/preservation/digital/formats/fdd/fdd000508.shtml
//      - MTL File Format information
// https://en.wikipedia.org/wiki/Wavefront_.obj_file
//      - OBJ File Format information