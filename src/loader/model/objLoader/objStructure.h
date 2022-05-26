//////////////////////////////////////////////////////////////////////
////    OBJ FILE STRUCTURE
////
////    Data Structures used to hold OBJ & MTL File data
////
////    Created by Darcy Lyndon Cukrov Wilson - 13/04/2022
//////////////////////////////////////////////////////////////////////

#include "math/Vector.h"

typedef Vector3Int faceDataTri[3];      //Stores the vertex to use, the texture coordinate, and the normal (f) (E.g. 8/11/7 = Vertex number/UV number/Normal number) (TRIS)
typedef Vector3Int faceDataPoly[4];     //Stores the vertex to use, the texture coordinate, and the normal (f) (E.g. 8/11/7 = Vertex number/UV number/Normal number) (POLYS)

typedef struct mtlData
{
    Vector3* ambientCol;                //The ambient colour of the material (Ka)
    Vector3* diffuseCol;                //The diffuse colour of the material (Kd)
    Vector3* specularCol;               //The specular colour of the material (Ks)

    float specularHigh;                 //The specular highlights in the material (Ns)
    float opticalDensity;               //The optical density highlights in the material (Ni)
    float transparent;                  //The transparency or dissolve of the material (d)

    unsigned illumination;              //Used for the illumination model of the material (illum)

    char* textureFileName;              //The name of the texture file to be used for the material (map_Kd)
} mtlData;

typedef struct objModel
{
    int nVert;                          //Number of vertices in the model
    int nUV;                            //Number of UVs in the model
    int nNormal;                        //Number of normals in the model
    int nFaces;                         //Number of faces in the model

    Vector3* vertData;                  //Stores the vertices of the model (v)
    Vector2* uvData;                    //Stores the UV data of each face (vt)
    Vector3* normalData;                //Stores the normals of each vertex (vn)

    mtlData materialData;               //The material data for the model

    faceDataTri* faceDataTriArray;      //A dynamic array to store each line of triangulated face data
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