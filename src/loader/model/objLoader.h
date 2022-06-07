#pragma once

//////////////////////////////////////////////////////////////////////
//  OBJ FILE LOADER
//
//  OBJ Loader for loading data from OBJ Files
//
//  Created by Darcy Lyndon Cukrov Wilson - 31/05/2022
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Included for strcmp()

#include "objStructure.h"

/**
 * @brief Loads Data from an OBJ File
 * @param const char* filePath - The filepath of the model
*/
objModel LoadOBJFile(const char* filePath); //Load and return the data for an OBJ File
/**
 * @brief Initialises the data of the OBJ to starting values
*/
objModel InitialiseData(); //Used to initialise the data within an OBJ Model
/**
 * @brief Allocates the memory needed for the OBJ File data
 * @param FILE* inputPointer - The file pointer for the OBJ File
*/
objModel AllocateModelMemory(FILE* inputPointer); //Allocates the memory needed for the model data
/**
 * @brief Finds the Index Offset of an OBJ Group (The lowest index value for each group)
 * @param objGroup inputData - A group within an OBJ File
*/
Vector3Int FindIndexOffset(objGroup inputData); //Finds the Index Offset of a given OBJ Group
/**
 * @brief Prints the data of an OBJ File (No group data is printed)
 * @param objModel inputData - The input OBJ File whose data is printed
*/
void PrintOBJData(objModel inputData); //Prints OBJ Data to screen to confirm the data
/**
 * @brief Prints the data of an OBJ File (Group Data is printed)
 * @param objModel inputData - The input OBJ File whose data is printed
*/
void PrintOBJGroupData(objModel inputData); //Prints OBJ Group Data to screen to confirm the data

/////////////////////////////////////////////////
//  REFERENCES
/////////////////////////////////////////////////

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// https://www.braynzarsoft.net/viewtutorial/q16390-22-loading-static-3d-models-obj-format
// http://netization.blogspot.com/2014/10/loading-obj-files-in-opengl.html
//      - OBJ Loader Tutorials
