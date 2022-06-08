#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "objStructure.h"

/**
 * @brief initialises a model in an obj file
 * @return the initialised model
*/
ObjModel InitialiseObjModel();

/**
 * @brief Initialises the data of the OBJ to starting values
 * @return the initilaised model
*/
ObjFile InitialiseObjFile();

/**
 * @brief Allocates the memory needed for the OBJ File data
 * @param FILE* inputPointer - The file pointer for the OBJ File
 * @return the initialised model
*/
ObjFile AllocateModelMemory(FILE* inputPointer);

/**
 * @brief Loads Data from an OBJ File
 * @param const char* filePath - The filepath of the model
*/
ObjFile LoadOBJFile(const char* filePath);

/**
 * @brief Finds the Index Offset of an OBJ Group (The lowest index value for each group)
 * @param ObjModel inputData - A group within an OBJ File
*/
Vector3Int FindIndexOffset(ObjModel inputData);

/**
 * @brief Prints the data of an OBJ File (No group data is printed)
 * @param ObjFile inputData - The input OBJ File whose data is printed
*/
void PrintOBJData(ObjFile inputData);