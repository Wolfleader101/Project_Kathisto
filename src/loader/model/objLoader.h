#pragma once

#include<string.h>

#include "objStructure.h"

objModel InitialiseData(); //Used to initialise the data within an OBJ Model
objModel LoadOBJFile(const char* filePath); //Load and return the data for an OBJ File
void PrintOBJData(objModel inputData); //Prints OBJ Data to screen to confirm the data