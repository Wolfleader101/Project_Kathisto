//////////////////////////////////////////////////////////////////////
//	VECTOR C IMPLEMENTATION
//
//  An implementation for C++-like vectors in C
//
//  Created by Darcy Lyndon Cukrov Wilson - 26/05/2022
//////////////////////////////////////////////////////////////////////

#include <stdio.h>

#define VECTOR_INITIAL_SIZE 1 //A Macro which defines the intial size of a Vector

typedef struct vector 
{
    void** vecItems; //The items within the Vector
    int vecSize; //The current size of the Vector
    int vecTotalElements; //The total number of elements within the Vector
} vector;

void Initialise_Vector(vector * inputVec); //Initialises the vector to be used
int Number_Of_Elements(vector * inputVec); //Returns the number of elements within the Vector
void Resize_Vector(vector * inputVec, int vecSize); //Resizes the Vector if the number of elements reaches the size limit
void Add_To_Vector(vector * inputVec, void* element); //Adds an item to the Vector
void Set_At_Vector_Index(vector * inputVec, int index, void * element); //Sets an item to the vector at a specific index within the current array of elements
void* Get_From_Vector_Index(vector * inputVec, int index); //Gets an item from the vector at a specific index
void Delete_Vector_Element(vector * inputVec, int index); //Deletes an Element from the vector at a specific index
void Free_Vector_Memory(vector * inputVec); //Frees the memory of the vector

/////////////////////////////////////////////////
//  REFERENCES
/////////////////////////////////////////////////

// https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
//      - Vectors in C Implemntation (Built off of this tutorial)