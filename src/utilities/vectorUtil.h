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

/**
 * @struct List of Vector 2's
 * @brief An implementation of Lists in the C language to contain Vector 2's
*/
typedef struct listVec2
{
    /**
     * @brief A list of Vector 2 elements
     */
    Vector2* vec2Items; //The items within the Vector
    /**
     * @brief The size of of the vector
     */
    int vecSize; //The current size of the Vector
    /**
     * @brief Total amount of elements in the vector
     */
    int vecTotalElements; //The total number of elements within the Vector
} listVec2;

/**
 * @brief Initialises a Vector2 List
 * @param listVec2* inputVec - The input list to be initialised
*/
void Vec2_InitialiseList(listVec2* inputVec); //Initialises the vector to be used
/**
 * @brief Resizes the list if the amount of elelemnts is equal tot he maximum size
 * @param listVec2* inputVec - The list to be resized
 * @param unsigned vecSize - The size of the list
*/
void Vec2_ResizeList(listVec2* inputVec, unsigned vecSize); //Resizes the Vector if the number of elements reaches the size limit
/**
 * @brief Adds new elements to the list
 * @param listVec2* inputVec - The list to be added to
 * @param Vector2 element - The vector element to be added
*/
void Vec2_AddToList(listVec2* inputVec, Vector2 element); //Adds an item to the Vector
/**
 * @brief Adds new elements to the list at a specific index
 * @param listVec2* inputVec - The list to be added to
 * @param unsigned index - The index which the element will be added to
 * @param Vector2 element - The vector element to be added
*/
void Vec2_SetAtListIndex(listVec2* inputVec, unsigned index, Vector2 element); //Sets an item to the vector at a specific index within the current array of elements
/**
 * @brief Returns a vector at a given index
 * @param listVec2* inputVec - The list to be taken from
 * @param unsigned index - The index which the element will be taken from
*/
Vector2 Vec2_GetFromListIndex(listVec2* inputVec, unsigned index); //Gets an item from the vector at a specific index
/**
 * @brief Frees the memory from a given list
 * @param listVec2* inputVec - The list whose memory is to be freed
*/
void Vec2_FreeListMemory(listVec2* inputVec); //Frees the memory of the vector

/////////////////////////////////////////////////
//  VECTOR3 LIST
/////////////////////////////////////////////////

/**
 * @struct List of Vector 3's
 * @brief An implementation of Lists in the C language to contain Vector 3's
*/
typedef struct listVec3 
{
    /**
     * @brief A list of Vector 3 elements
     */
    Vector3 *vec3Items; //The items within the Vector
    /**
     * @brief The size of of the vector
     */
    int vecSize; //The current size of the Vector
    /**
     * @brief Total amount of elements in the vector
     */
    int vecTotalElements; //The total number of elements within the Vector
} listVec3;

/**
 * @brief Initialises a Vector3 List
 * @param listVec3* inputVec - The input list to be initialised
*/
void Vec3_InitialiseList(listVec3* inputVec); //Initialises the vector to be used
/**
 * @brief Resizes the list if the amount of elelemnts is equal tot he maximum size
 * @param listVec3* inputVec - The list to be resized
 * @param unsigned vecSize - The size of the list
*/
void Vec3_ResizeList(listVec3* inputVec, unsigned vecSize); //Resizes the Vector if the number of elements reaches the size limit
/**
 * @brief Adds new elements to the list
 * @param listVec3* inputVec - The list to be added to
 * @param Vector3 element - The vector element to be added
*/
void Vec3_AddToList(listVec3* inputVec, Vector3 element); //Adds an item to the Vector
/**
 * @brief Adds new elements to the list at a specific index
 * @param listVec3* inputVec - The list to be added to
 * @param unsigned index - The index which the element will be added to
 * @param Vector3 element - The vector element to be added
*/
void Vec3_SetAtListIndex(listVec3* inputVec, unsigned index, Vector3 element); //Sets an item to the vector at a specific index within the current array of elements
/**
 * @brief Returns a vector at a given index
 * @param listVec3* inputVec - The list to be taken from
 * @param unsigned index - The index which the element will be taken from
*/
Vector3 Vec3_GetFromListIndex(listVec3* inputVec, unsigned index); //Gets an item from the vector at a specific index
/**
 * @brief Frees the memory from a given list
 * @param listVec3* inputVec - The list whose memory is to be freed
*/
void Vec3_FreeListMemory(listVec3* inputVec); //Frees the memory of the vector

/////////////////////////////////////////////////
//  VECTOR3 INT LIST
/////////////////////////////////////////////////

/**
 * @struct List of Vector 3 Ints
 * @brief An implementation of Lists in the C language to contain Vector 3 Int
*/
typedef struct listVec3Int
{
    /**
     * @brief A list of Vector 3 Int elements
     */
    Vector3Int* vec3IntItems; //The items within the Vector
    /**
     * @brief The size of of the vector
     */
    int vecSize; //The current size of the Vector
    /**
     * @brief Total amount of elements in the vector
     */
    int vecTotalElements; //The total number of elements within the Vector
} listVec3Int;

/**
 * @brief Initialises a Vector3Int List
 * @param listVec3Int* inputVec - The input list to be initialised
*/
void Vec3Int_InitialiseList(listVec3Int* inputVec); //Initialises the vector to be used
/**
 * @brief Resizes the list if the amount of elelemnts is equal tot he maximum size
 * @param listVec3Int* inputVec - The list to be resized
 * @param unsigned vecSize - The size of the list
*/
void Vec3Int_ResizeList(listVec3Int* inputVec, unsigned vecSize); //Resizes the Vector if the number of elements reaches the size limit
/**
 * @brief Adds new elements to the list
 * @param listVec3Int* inputVec - The list to be added to
 * @param Vector3Int element - The vector element to be added
*/
void Vec3Int_AddToList(listVec3Int* inputVec, Vector3Int element); //Adds an item to the Vector
/**
 * @brief Adds new elements to the list at a specific index
 * @param listVec3Int* inputVec - The list to be added to
 * @param unsigned index - The index which the element will be added to
 * @param Vector3Int element - The vector element to be added
*/
void Vec3Int_SetAtListIndex(listVec3Int* inputVec, unsigned index, Vector3Int element); //Sets an item to the vector at a specific index within the current array of elements
/**
 * @brief Returns a vector at a given index
 * @param listVec3Int* inputVec - The list to be taken from
 * @param unsigned index - The index which the element will be taken from
*/
Vector3Int Vec3Int_GetFromListIndex(listVec3Int* inputVec, unsigned index); //Gets an item from the vector at a specific index
/**
 * @brief Frees the memory from a given list
 * @param listVec3Int* inputVec - The list whose memory is to be freed
*/
void Vec3Int_FreeListMemory(listVec3Int* inputVec); //Frees the memory of the vector

/////////////////////////////////////////////////
//  REFERENCES
/////////////////////////////////////////////////

// https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
//      - Vectors in C Implemntation (Built off of this tutorial)