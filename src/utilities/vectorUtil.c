#include "vectorUtil.h"

void Initialise_Vector(vector * inputVec) //Initialises the vector to be used
{
	inputVec->vecSize = VECTOR_INITIAL_SIZE; //Sets the intial size of the Vector to the defined Macro

	inputVec->vecTotalElements = 0; //Sets the number of elements within the Vector to 0

	inputVec->vecItems = malloc(sizeof(void*) * VECTOR_INITIAL_SIZE); //Allocates the memory for the Vector
}

int Number_Of_Elements(vector * inputVec) //Returns the number of elements within the Vector
{
	return inputVec->vecTotalElements; //Returns the total number of elements within the vector
}

void Resize_Vector(vector * inputVec, int vecSize) //Resizes the Vector if the number of elements reaches the size limit
{
	void** items = realloc(inputVec->vecItems, sizeof(void*) * vecSize); //Creates a new temporary 2D Array to replace the old vector and allocates the memory

	if(items) //If the array has been allocated successfully
	{
		inputVec->vecItems = items; //Set the memory to the address of the new vector

		inputVec->vecSize = vecSize; //Set the current size to the new input size
	}
}

void Add_To_Vector(vector * inputVec, void * element) //Adds an item to the Vector
{
	if (inputVec->vecSize == inputVec->vecTotalElements) //If the amount of elelemts within the vector is equal to the vector's size
	{
		Resize_Vector(inputVec, inputVec->vecSize * 2); //Resize the element with double it's current size
	}

	inputVec->vecItems[inputVec->vecTotalElements++] = element; //Add the new element to the vector, and increase the element count
}

void Set_At_Vector_Index(vector * inputVec, int index, void* element) //Sets an item to the vector at a specific index within the current array of elements
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		inputVec->vecItems[index] = element; //Replace an existing element with a new element
	}
}

void * Get_From_Vector_Index(vector * inputVec, int index) //Gets an item from the vector at a specific index
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		return inputVec->vecItems[index]; //Returns the element from the Vector
	}
}

void Delete_Vector_Element(vector * inputVec, int index) //Deletes an Element from the vector at a specific index
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

	if((inputVec->vecTotalElements > 0) && (inputVec->vecTotalElements == (inputVec->vecSize / 4))) //If the amount of elements is greater than 0 and the number of elements is equal to the vector size divided by 4
	{
		Resize_Vector(inputVec, inputVec->vecSize / 2); //Half the size of the vector
	}
}

void Free_Vector_Memory(vector * inputVec) //Frees the memory of the vector
{
	free(inputVec->vecItems); //Frees the memory from the Vector
}