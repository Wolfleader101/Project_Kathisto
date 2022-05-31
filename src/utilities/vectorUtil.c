#include "vectorUtil.h"

void InitialiseVector(list* inputVec) //Initialises the vector to be used
{
	inputVec->vecSize = VECTOR_INITIAL_SIZE; //Sets the intial size of the Vector to the defined Macro

	inputVec->vecTotalElements = 0; //Sets the number of elements within the Vector to 0

	inputVec->vecItems = malloc(sizeof(void*) * inputVec->vecSize); //Allocates the memory for the Vector
}

void ResizeVector(list* inputVec, unsigned vecSize) //Resizes the Vector if the number of elements reaches the size limit
{
	Vector3* items = realloc(inputVec->vecItems, sizeof(Vector3) * vecSize); //Creates a new temporary 2D Array to replace the old vector and allocates the memory

	if(items) //If the array has been allocated successfully
	{
		inputVec->vecItems = items; //Set the memory to the address of the new vector

		inputVec->vecSize = vecSize; //Set the current size to the new input size
	}
}

void AddToVector(list* inputVec, Vector3 element) //Adds an item to the Vector
{
	if (inputVec->vecSize == inputVec->vecTotalElements) //If the amount of elelemts within the vector is equal to the vector's size
	{
		ResizeVector(inputVec, inputVec->vecSize * 2); //Resize the element with double it's current size
	}

	inputVec->vecItems[inputVec->vecTotalElements++] = element; //Add the new element to the vector, and increase the element count
}

void SetAtVectorIndex(list* inputVec, unsigned index, Vector3 element) //Sets an item to the vector at a specific index within the current array of elements
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		inputVec->vecItems[index] = element; //Replace an existing element with a new element
	}
}

Vector3 GetFromVectorIndex(list* inputVec, unsigned index) //Gets an item from the vector at a specific index
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		return inputVec->vecItems[index]; //Returns the element from the Vector
	}
	else
		printf("ERROR: Index %d is outside of the bounds of the Vector!", index);
}

void DeleteVectorElement(list* inputVec, unsigned index) //Deletes an Element from the vector at a specific index
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		return; //Returns from the function
	}

	inputVec->vecItems[index] = NULL; //Nulls the element from the array

	for (unsigned i = 0; i < inputVec->vecTotalElements - 1; i++) //Loops through all of the elements in the Vector minus 1
	{
		inputVec->vecItems[i] = inputVec->vecItems[i + 1]; //Sets the current element to be equal to the next element

		inputVec->vecItems[i + 1] = NULL; //Sets the next element to Null
	}

	inputVec->vecTotalElements--; //Removes one element from the element count
}

void FreeVectorMemory(list* inputVec) //Frees the memory of the vector
{
	free(inputVec->vecItems); //Frees the memory from the Vector
}