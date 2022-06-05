#pragma once

//////////////////////////////////////////////////////////////////////
//	VECTOR (LIST) C IMPLEMENTATION
//
//  An implementation for C++-like vectors in C (Called lists here to not
//  confuse ourselves with our other vectors)
// 
//  NOTE: Only works for types such as ints, char pointers, floats, etc.
//  Does not appear to work for custom structs like our Vectors
//
//  Created by Darcy Lyndon Cukrov Wilson - 26/05/2022
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "math/Vector.h"

#define VECTOR_INITIAL_SIZE 1 //A Macro which defines the intial size of a Vector

/////////////////////////////////////////////////
//  VECTOR2 LIST
/////////////////////////////////////////////////

typedef struct listVec2
{
    Vector2* vec2Items; //The items within the Vector
    int vecSize; //The current size of the Vector
    int vecTotalElements; //The total number of elements within the Vector
} listVec2;

void Vec2_InitialiseList(listVec2* inputVec); //Initialises the vector to be used
void Vec2_ResizeList(listVec2* inputVec, unsigned vecSize); //Resizes the Vector if the number of elements reaches the size limit
void Vec2_AddToList(listVec2* inputVec, Vector2 element); //Adds an item to the Vector
void Vec2_SetAtListIndex(listVec2* inputVec, unsigned index, Vector2 element); //Sets an item to the vector at a specific index within the current array of elements
Vector2 Vec2_GetFromListIndex(listVec2* inputVec, unsigned index); //Gets an item from the vector at a specific index
void Vec2_FreeListMemory(listVec2* inputVec); //Frees the memory of the vector

/////////////////////////////////////////////////
//  VECTOR3 LIST
/////////////////////////////////////////////////

typedef struct listVec3 
{
    Vector3 *vec3Items; //The items within the Vector
    int vecSize; //The current size of the Vector
    int vecTotalElements; //The total number of elements within the Vector
} listVec3;

void Vec3_InitialiseList(listVec3* inputVec); //Initialises the vector to be used
void Vec3_ResizeList(listVec3* inputVec, unsigned vecSize); //Resizes the Vector if the number of elements reaches the size limit
void Vec3_AddToList(listVec3* inputVec, Vector3 element); //Adds an item to the Vector
void Vec3_SetAtListIndex(listVec3* inputVec, unsigned index, Vector3 element); //Sets an item to the vector at a specific index within the current array of elements
Vector3 Vec3_GetFromListIndex(listVec3* inputVec, unsigned index); //Gets an item from the vector at a specific index
void Vec3_FreeListMemory(listVec3* inputVec); //Frees the memory of the vector

/////////////////////////////////////////////////
//  VECTOR3 INT LIST
/////////////////////////////////////////////////

typedef struct listVec3Int
{
    Vector3Int* vec3IntItems; //The items within the Vector
    int vecSize; //The current size of the Vector
    int vecTotalElements; //The total number of elements within the Vector
} listVec3Int;

void Vec3Int_InitialiseList(listVec3Int* inputVec); //Initialises the vector to be used
void Vec3Int_ResizeList(listVec3Int* inputVec, unsigned vecSize); //Resizes the Vector if the number of elements reaches the size limit
void Vec3Int_AddToList(listVec3Int* inputVec, Vector3Int element); //Adds an item to the Vector
void Vec3Int_SetAtListIndex(listVec3Int* inputVec, unsigned index, Vector3Int element); //Sets an item to the vector at a specific index within the current array of elements
Vector3Int Vec3Int_GetFromListIndex(listVec3Int* inputVec, unsigned index); //Gets an item from the vector at a specific index
void Vec3Int_FreeListMemory(listVec3Int* inputVec); //Frees the memory of the vector

/////////////////////////////////////////////////
//  REFERENCES
/////////////////////////////////////////////////

// https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
//      - Vectors in C Implemntation (Built off of this tutorial)