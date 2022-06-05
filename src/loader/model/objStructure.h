#pragma once
//////////////////////////////////////////////////////////////////////
//  OBJ FILE STRUCTURE
//
//  Data Structures used to hold OBJ data (BASIC REPRESENTATION)
//
//  Created by Darcy Lyndon Cukrov Wilson - 13/04/2022
//////////////////////////////////////////////////////////////////////

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