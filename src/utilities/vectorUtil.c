#include "vectorUtil.h"

/////////////////////////////////////////////////
//  VECTOR2 LIST
/////////////////////////////////////////////////

void Vec2_InitialiseList(listVec2* inputVec) //Initialises the vector to be used
{
	inputVec->vecSize = VECTOR_INITIAL_SIZE; //Sets the intial size of the Vector to the defined Macro

	inputVec->vecTotalElements = 0; //Sets the number of elements within the Vector to 0

	inputVec->vec2Items = malloc(sizeof(Vector2) * inputVec->vecSize); //Allocates the memory for the Vector
}

void Vec2_ResizeList(listVec2* inputVec, unsigned vecSize) //Resizes the Vector if the number of elements reaches the size limit
{
	Vector3* items = realloc(inputVec->vec2Items, sizeof(Vector2) * vecSize); //Creates a new temporary 2D Array to replace the old vector and allocates the memory

	if (items) //If the array has been allocated successfully
	{
		inputVec->vec2Items = items; //Set the memory to the address of the new vector

		inputVec->vecSize = vecSize; //Set the current size to the new input size
	}
}

void Vec2_AddToList(listVec2* inputVec, Vector2 element) //Adds an item to the Vector
{
	if (inputVec->vecSize == inputVec->vecTotalElements) //If the amount of elelemts within the vector is equal to the vector's size
	{
		Vec2_ResizeList(inputVec, inputVec->vecSize * 2); //Resize the element with double it's current size
	}

	inputVec->vec2Items[inputVec->vecTotalElements++] = element; //Add the new element to the vector, and increase the element count
}

void Vec2_SetAtListIndex(listVec2* inputVec, unsigned index, Vector2 element) //Sets an item to the vector at a specific index within the current array of elements
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		inputVec->vec2Items[index] = element; //Replace an existing element with a new element
	}
}

Vector2 Vec2_GetFromListIndex(listVec2* inputVec, unsigned index) //Gets an item from the vector at a specific index
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		return inputVec->vec2Items[index]; //Returns the element from the Vector
	}
	else
		printf("ERROR: Index %d is outside of the bounds of the Vector!", index);
}

void Vec2_FreeListMemory(listVec2* inputVec) //Frees the memory of the vector
{
	free(inputVec->vec2Items); //Frees the memory from the Vector
}

/////////////////////////////////////////////////
//  VECTOR3 LIST
/////////////////////////////////////////////////

void Vec3_InitialiseList(listVec3* inputVec) //Initialises the vector to be used
{
	inputVec->vecSize = VECTOR_INITIAL_SIZE; //Sets the intial size of the Vector to the defined Macro

	inputVec->vecTotalElements = 0; //Sets the number of elements within the Vector to 0

	inputVec->vec3Items = malloc(sizeof(Vector3) * inputVec->vecSize); //Allocates the memory for the Vector
}

void Vec3_ResizeList(listVec3* inputVec, unsigned vecSize) //Resizes the Vector if the number of elements reaches the size limit
{
	Vector3* items = realloc(inputVec->vec3Items, sizeof(Vector3) * vecSize); //Creates a new temporary 2D Array to replace the old vector and allocates the memory

	if(items) //If the array has been allocated successfully
	{
		inputVec->vec3Items = items; //Set the memory to the address of the new vector

		inputVec->vecSize = vecSize; //Set the current size to the new input size
	}
}

void Vec3_AddToList(listVec3* inputVec, Vector3 element) //Adds an item to the Vector
{
	if (inputVec->vecSize == inputVec->vecTotalElements) //If the amount of elelemts within the vector is equal to the vector's size
	{
		Vec3_ResizeList(inputVec, inputVec->vecSize * 2); //Resize the element with double it's current size
	}

	inputVec->vec3Items[inputVec->vecTotalElements++] = element; //Add the new element to the vector, and increase the element count
}

void Vec3_SetAtListIndex(listVec3* inputVec, unsigned index, Vector3 element) //Sets an item to the vector at a specific index within the current array of elements
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		inputVec->vec3Items[index] = element; //Replace an existing element with a new element
	}
}

Vector3 Vec3_GetFromListIndex(listVec3* inputVec, unsigned index) //Gets an item from the vector at a specific index
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		return inputVec->vec3Items[index]; //Returns the element from the Vector
	}
	else
		printf("ERROR: Index %d is outside of the bounds of the Vector!", index);
}

void Vec3_FreeListMemory(listVec3* inputVec) //Frees the memory of the vector
{
	free(inputVec->vec3Items); //Frees the memory from the Vector
}

/////////////////////////////////////////////////
//  VECTOR3 INT LIST
/////////////////////////////////////////////////

void Vec3Int_InitialiseList(listVec3Int* inputVec) //Initialises the vector to be used
{
	inputVec->vecSize = VECTOR_INITIAL_SIZE; //Sets the intial size of the Vector to the defined Macro

	inputVec->vecTotalElements = 0; //Sets the number of elements within the Vector to 0

	inputVec->vec3IntItems = malloc(sizeof(Vector3Int) * inputVec->vecSize); //Allocates the memory for the Vector
}

void Vec3Int_ResizeList(listVec3Int* inputVec, unsigned vecSize) //Resizes the Vector if the number of elements reaches the size limit
{
	Vector3* items = realloc(inputVec->vec3IntItems, sizeof(Vector3Int) * vecSize); //Creates a new temporary 2D Array to replace the old vector and allocates the memory

	if (items) //If the array has been allocated successfully
	{
		inputVec->vec3IntItems = items; //Set the memory to the address of the new vector

		inputVec->vecSize = vecSize; //Set the current size to the new input size
	}
}

void Vec3Int_AddToList(listVec3Int* inputVec, Vector3Int element) //Adds an item to the Vector
{
	if (inputVec->vecSize == inputVec->vecTotalElements) //If the amount of elelemts within the vector is equal to the vector's size
	{
		Vec3Int_ResizeList(inputVec, inputVec->vecSize * 2); //Resize the element with double it's current size
	}

	inputVec->vec3IntItems[inputVec->vecTotalElements++] = element; //Add the new element to the vector, and increase the element count
}

void Vec3Int_SetAtListIndex(listVec3Int* inputVec, unsigned index, Vector3Int element) //Sets an item to the vector at a specific index within the current array of elements
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		inputVec->vec3IntItems[index] = element; //Replace an existing element with a new element
	}
}

Vector3Int Vec3Int_GetFromListIndex(listVec3Int* inputVec, unsigned index) //Gets an item from the vector at a specific index
{
	if (index >= 0 && index < inputVec->vecTotalElements) //If the index is greater than or equal to 0, and it's within the limit of already set elements
	{
		return inputVec->vec3IntItems[index]; //Returns the element from the Vector
	}
	else
		printf("ERROR: Index %d is outside of the bounds of the Vector!", index);
}

void Vec3Int_FreeListMemory(listVec3Int* inputVec) //Frees the memory of the vector
{
	free(inputVec->vec3IntItems); //Frees the memory from the Vector
}