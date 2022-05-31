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

typedef struct listVec3 
{
    Vector3 vecItems; //The items within the Vector
    int vecSize; //The current size of the Vector
    int vecTotalElements; //The total number of elements within the Vector
} list;

void InitialiseVector(list* inputVec); //Initialises the vector to be used
void ResizeVector(list* inputVec, unsigned vecSize); //Resizes the Vector if the number of elements reaches the size limit
void AddToVector(list* inputVec, Vector3 element); //Adds an item to the Vector
void SetAtVectorIndex(list* inputVec, unsigned index, Vector3 element); //Sets an item to the vector at a specific index within the current array of elements
Vector3 GetFromVectorIndex(list* inputVec, unsigned index); //Gets an item from the vector at a specific index
void DeleteVectorElement(list* inputVec, unsigned index); //Deletes an Element from the vector at a specific index
void FreeVectorMemory(list* inputVec); //Frees the memory of the vector

/////////////////////////////////////////////////
//  REFERENCES
/////////////////////////////////////////////////

// https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
//      - Vectors in C Implemntation (Built off of this tutorial)