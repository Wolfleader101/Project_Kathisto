//////////////////////////////////////////////////////////////////////
////    OBJ FILE STRUCTURE
////
////    Data Structures used to hold OBJ data
////
////    Created by Darcy Lyndon Cukrov Wilson - 13/04/2022
//////////////////////////////////////////////////////////////////////

#include "math/Vector.h"

typedef struct objModel
{
    int nVert;                          //Number of vertices in the model
    int nUV;                            //Number of UVs in the model
    int nNormal;                        //Number of normals in the model
    int nFaces;                         //Number of faces in the model

    Vector3* vertPosition;              //Stores the position of a vertex (v)
    Vector2* textureCoord;              //Stores the texture coordinate of each vertex (vt)
    Vector3* normalData;                //Stores the normals of each vertex (vn)

    Vector3Int* vertexPosIndicies;
    Vector3Int* normalIndicies;
    Vector3Int* textureCoordIndicies;
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