#pragma once

//////////////////////////////////////////////////////////////////////
//  OBJ FILE LOADER
//
//  OBJ Loader for loading data from OBJ Files
//
//  Created by Darcy Lyndon Cukrov Wilson - 31/05/2022
//////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<string.h> //Included for strcmp()

#include "objStructure.h"

objModel LoadOBJFile(const char* filePath); //Load and return the data for an OBJ File
objModel InitialiseData(); //Used to initialise the data within an OBJ Model
objModel AllocateModelMemory(FILE* inputPointer); //Allocates the memory needed for the model data
void PrintOBJData(objModel inputData); //Prints OBJ Data to screen to confirm the data

/////////////////////////////////////////////////
//  REFERENCES
/////////////////////////////////////////////////

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// https://www.braynzarsoft.net/viewtutorial/q16390-22-loading-static-3d-models-obj-format
// http://netization.blogspot.com/2014/10/loading-obj-files-in-opengl.html
//      - OBJ Loader Tutorials
