#include "objLoader.h"

objModel LoadOBJFile(const char* filePath) //Load and return the data for an OBJ File
{
	FILE* filePointer = NULL; //File pointer to OBJ File
	int lineResult; //Checks the results of an fscanf of a line

	unsigned vertIndex = 0; //The counter which adds data to vertex position array
	unsigned texCoordIndex = 0; //The counter which adds data to the texture coordinate array
	unsigned normalIndex = 0; //The counter which adds data to the vertex normal array

	unsigned faceIndex = 0; //The counter which adds data to the face index arrays
	
	objModel objData = InitialiseData(); //Data to be passed back (Initialise first)

	Vector3 vec3_tmpData1; //Temporary Vector3 used to store data to pass into the Lists
	Vector3Int vec3Int_tmpData1, vec3Int_tmpData2, vec3Int_tmpData3; //Temporary Vector3Int's used to store data to pass into the Lists
	Vector2 vec2_tmpData1; //Temporary Vector2 used to store data to pass into the Lists

	filePointer = fopen(filePath, "r"); //Opens the file
	if(filePointer == NULL) //Checks to see if the file has opened
	{
		perror("ERROR");

		exit(1);
	}

	objData = AllocateModelMemory(filePointer);

	while (1) //Loops while not equal to the End of File (EOF)
	{
		char lineBuffer[128] = ""; //Each line of the file is read into the buffer

		int lineResult = fscanf(filePointer, "%s", lineBuffer); //Reads the first word of the line

		if (lineResult == EOF) //Checks to see if the result of the line read is an End of File (EOF)
		{
			break; //Breaks from the loop of End of File (EOF) is reached
		}

		if (strcmp(lineBuffer, "v") == 0) //Checks to see if the line contains 'v' (Vertex)
		{
			fscanf(filePointer, "%f %f %f\n", &vec3_tmpData1.x, &vec3_tmpData1.y, &vec3_tmpData1.z); //Reads data into temporary container

			objData.vertPosition[vertIndex] = vec3_tmpData1; //Adds to the array

			vertIndex++;
		}

		if (strcmp(lineBuffer, "vt") == 0) //Checks to see if the line contains 'vt' (Vertex Texture)
		{
			fscanf(filePointer, "%f %f\n", &vec2_tmpData1.x, &vec2_tmpData1.y); //Reads data into temporary container

			objData.textureCoord[texCoordIndex] = vec2_tmpData1; //Adds to the array

			texCoordIndex++;
		}

		if (strcmp(lineBuffer, "vn") == 0) //Checks to see if the line contains 'vn' (Vertex Normal)
		{
			fscanf(filePointer, "%f %f %f\n", &vec3_tmpData1.x, &vec3_tmpData1.y, &vec3_tmpData1.z); //Reads data into temporary container

			objData.normalData[normalIndex] = vec3_tmpData1; //Adds to the array

			normalIndex++;
		}

		if (strcmp(lineBuffer, "f") == 0) //Checks to see if the line contains 'f' (Face)
		{
			int vertsInFace = fscanf(filePointer, "%d/%d/%d %d/%d/%d %d/%d/%d\n",	&vec3Int_tmpData1.x, &vec3Int_tmpData2.x, &vec3Int_tmpData3.x,	//Vertex Index 1 | UV Index 1 | Normal Index 1
																					&vec3Int_tmpData1.y, &vec3Int_tmpData2.y, &vec3Int_tmpData3.y,	//Vertex Index 2 | UV Index 2 | Normal Index 2
																					&vec3Int_tmpData1.z, &vec3Int_tmpData2.z, &vec3Int_tmpData3.z);	//Vertex Index 3 | UV Index 3 | Normal Index 3

			vertsInFace /= 3; //Converts it into the number of vertexes (3 = Triangles, 4 = Quads, etc.)

			if (vertsInFace != 3) //Checks to see if the file is triangulated
			{
				printf("ERROR: File is not triangulated! Please edit the file and triangulate all faces!\n");

				exit(0);
			}

			//REMOVES 1 FROM EACH FACE ELEMENT TO MAKE IT START AT 0
			vec3Int_tmpData1.x -= 1;
			vec3Int_tmpData2.x -= 1;
			vec3Int_tmpData3.x -= 1;
			vec3Int_tmpData1.y -= 1;
			vec3Int_tmpData2.y -= 1;
			vec3Int_tmpData3.y -= 1;
			vec3Int_tmpData1.z -= 1;
			vec3Int_tmpData2.z -= 1;
			vec3Int_tmpData3.z -= 1;

			objData.vertexPosIndicies[faceIndex] = vec3Int_tmpData1; //Adds to the array
			objData.normalIndicies[faceIndex] = vec3Int_tmpData2; //Adds to the array
			objData.textureCoordIndicies[faceIndex] = vec3Int_tmpData3; //Adds to the array

			faceIndex++;
		}
	}

	rewind(filePointer); //Resets the reading to the beggining of the file

	if(objData.nGroups > 0)
	{
		char* previousBuffer = ""; //The bufefr from the prvious line
		unsigned groupCounter = 0; //The counter which adds data to the next group

		vertIndex = 0; //The counter which adds data to vertex position array
		texCoordIndex = 0; //The counter which adds data to the texture coordinate array
		normalIndex = 0; //The counter which adds data to the vertex normal array

		faceIndex = 0; //The counter which adds data to the face index arrays
		
		while (1) //Loops while not equal to the End of File (EOF)
		{
			char currentBuffer[128] = ""; //Each line of the file is read into the buffer

			int lineResult = fscanf(filePointer, "%s", currentBuffer); //Reads the first word of the line

			if (lineResult == EOF) //Checks to see if the result of the line read is an End of File (EOF)
			{
				break; //Breaks from the loop of End of File (EOF) is reached
			}

			if ((strcmp(currentBuffer, "v") == 0) && (strcmp(previousBuffer, "v") == -1)) //Checks to see if the reader has moved to the next grou[
			{
				groupCounter++;
			}

			if (strcmp(currentBuffer, "v") == 0 && groupCounter < objData.nGroups) //Checks to see if the line contains 'v' (Vertex)
			{
				fscanf(filePointer, "%f %f %f\n", &vec3_tmpData1.x, &vec3_tmpData1.y, &vec3_tmpData1.z); //Reads data into temporary container

				objData.modelGroups[groupCounter].vertPosition[vertIndex] = vec3_tmpData1; //Adds to the array

				vertIndex++;
			}

			if (strcmp(currentBuffer, "vt") == 0 && groupCounter < objData.nGroups) //Checks to see if the line contains 'vt' (Vertex Texture)
			{
				fscanf(filePointer, "%f %f\n", &vec2_tmpData1.x, &vec2_tmpData1.y); //Reads data into temporary container

				objData.modelGroups[groupCounter].textureCoord[texCoordIndex] = vec2_tmpData1; //Adds to the array

				texCoordIndex++;
			}

			if (strcmp(currentBuffer, "vn") == 0 && groupCounter < objData.nGroups) //Checks to see if the line contains 'vn' (Vertex Normal)
			{
				fscanf(filePointer, "%f %f %f\n", &vec3_tmpData1.x, &vec3_tmpData1.y, &vec3_tmpData1.z); //Reads data into temporary container

				Vec3_AddToList(&objData.normalData, vec3_tmpData1); //Adds to the list

				objData.modelGroups[groupCounter].normalData[normalIndex] = vec3_tmpData1; //Adds to the array

				normalIndex++;
			}

			if (strcmp(currentBuffer, "f") == 0 && groupCounter < objData.nGroups) //Checks to see if the line contains 'f' (Face)
			{
				int vertsInFace = fscanf(filePointer, "%d/%d/%d %d/%d/%d %d/%d/%d\n",	&vec3Int_tmpData1.x, &vec3Int_tmpData2.x, &vec3Int_tmpData3.x,	//Vertex Index 1 | UV Index 1 | Normal Index 1
																						&vec3Int_tmpData1.y, &vec3Int_tmpData2.y, &vec3Int_tmpData3.y,	//Vertex Index 2 | UV Index 2 | Normal Index 2
																						&vec3Int_tmpData1.z, &vec3Int_tmpData2.z, &vec3Int_tmpData3.z);	//Vertex Index 3 | UV Index 3 | Normal Index 3

				vertsInFace /= 3; //Converts it into the number of vertexes (3 = Triangles, 4 = Quads, etc.)

				if (vertsInFace != 3) //Checks to see if the file is triangulated
				{
					printf("ERROR: File is not triangulated! Please edit the file and triangulate all faces!\n");

					exit(0);
				}

				//ADDS DATA TO GROUP
				objData.modelGroups[groupCounter].grpVertexIndicies[faceIndex] = vec3Int_tmpData1; //Adds to the array
				objData.modelGroups[groupCounter].grpNormalIndicies[faceIndex] = vec3Int_tmpData2; //Adds to the array
				objData.modelGroups[groupCounter].grpUVIndicies[faceIndex] = vec3Int_tmpData3; //Adds to the array

				faceIndex++;
			}

			strcpy(previousBuffer, currentBuffer);
		}
	}

	fclose(filePointer); //Closes the file

	return(objData); //Return data
}

objModel InitialiseData() //Used to initialise the data within an OBJ Model
{
	objModel initialisedData; //Data to be passed back

	initialisedData.modelName = "";

	//Initialises the amounts of faces, normals, uvs and verts to 0
	initialisedData.nFaces = 0;
	initialisedData.nNormals = 0;
	initialisedData.nUVs = 0;
	initialisedData.nVerts = 0;
	initialisedData.nGroups = 0;

	//Initialises the arrays for the model data
	initialisedData.vertPosition = NULL;
	initialisedData.textureCoord = NULL;
	initialisedData.normalData = NULL;

	//Initialises the arrays for the face indicies
	initialisedData.vertexPosIndicies = NULL;
	initialisedData.normalIndicies = NULL;
	initialisedData.textureCoordIndicies = NULL;

	//Initialises the arrays for the model group data
	initialisedData.modelGroups = NULL;

	return(initialisedData); //Return initialised data
}

objModel AllocateModelMemory(FILE* inputPointer)
{
	objModel memoryAllocated = InitialiseData();
	
	//FINDS THE AMOUNT OF ITEMS WITHIN THE MODEL
	while (1) //Loops while not equal to the End of File (EOF)
	{
		char lineBuffer[128] = ""; //Each line of the file is read into the buffer

		int lineResult = fscanf(inputPointer, "%s", lineBuffer); //Reads the first word of the line

		if (lineResult == EOF) //Checks to see if the result of the line read is an End of File (EOF)
		{
			break; //Breaks from the loop of End of File (EOF) is reached
		}

		if (strcmp(lineBuffer, "v") == 0) //Checks to see if the line contains 'v' (Vertex)
		{
			memoryAllocated.nVerts++; //Adds one count to the number of verticies
		}

		if (strcmp(lineBuffer, "vt") == 0) //Checks to see if the line contains 'vt' (Vertex Texture)
		{
			memoryAllocated.nUVs++; //Adds one count to the number of UVs
		}

		if (strcmp(lineBuffer, "vn") == 0) //Checks to see if the line contains 'vn' (Vertex Normal)
		{
			memoryAllocated.nNormals++; //Adds one count to the number of normals
		}

		if (strcmp(lineBuffer, "g") == 0) //Checks to see if the line contains 'g' (Group)
		{
			memoryAllocated.nGroups++; //Adds one count to the number of groups
		}

		if (strcmp(lineBuffer, "f") == 0) //Checks to see if the line contains 'f' (Face)
		{
			memoryAllocated.nFaces++; //Adds one count to the number of faces
		}
	}

	if(memoryAllocated.nGroups > 0)
	{
		rewind(inputPointer); //Resets the reading to the beggining of the file
		
		memoryAllocated.modelGroups = malloc(sizeof(objGroup) * memoryAllocated.nGroups); //Allocates the memory for the array

		for(unsigned i = 0; i < memoryAllocated.nGroups; i++) //Initialise the number of variables
		{
			memoryAllocated.modelGroups[i].nVerts = 0;
			memoryAllocated.modelGroups[i].nUVs = 0;
			memoryAllocated.modelGroups[i].nNormals = 0;
			memoryAllocated.modelGroups[i].nFaces = 0;
		}

		char* previousBuffer = ""; //The bufefr from the prvious line
		unsigned groupCounter = 0; //The counter which adds data to the next group

		while (1) //Loops while not equal to the End of File (EOF)
		{
			char currentBuffer[128] = ""; //Each line of the file is read into the buffer

			int lineResult = fscanf(inputPointer, "%s", currentBuffer); //Reads the first word of the line

			if (lineResult == EOF) //Checks to see if the result of the line read is an End of File (EOF)
			{
				break; //Breaks from the loop of End of File (EOF) is reached
			}

			if ((strcmp(currentBuffer, "v") == 0) && (strcmp(previousBuffer, "v") == -1)) //Checks to see if the reader has moved to the next grou[
			{
				groupCounter++;
			}

			if (strcmp(currentBuffer, "v") == 0 && groupCounter < memoryAllocated.nGroups) //Checks to see if the line contains 'v' (Vertex)
			{
				memoryAllocated.modelGroups[groupCounter].nVerts++;
			}

			if (strcmp(currentBuffer, "vt") == 0 && groupCounter < memoryAllocated.nGroups) //Checks to see if the line contains 'vt' (Vertex Texture)
			{
				memoryAllocated.modelGroups[groupCounter].nUVs++;
			}

			if (strcmp(currentBuffer, "vn") == 0 && groupCounter < memoryAllocated.nGroups) //Checks to see if the line contains 'vn' (Vertex Normal)
			{
				memoryAllocated.modelGroups[groupCounter].nNormals++;
			}

			if (strcmp(currentBuffer, "f") == 0 && groupCounter < memoryAllocated.nGroups) //Checks to see if the line contains 'f' (Face)
			{
				memoryAllocated.modelGroups[groupCounter].nFaces++;
			}

			strcpy(previousBuffer, currentBuffer);
		}

		for (unsigned i = 0; i < memoryAllocated.nGroups; i++) //Initialise the number of variables
		{
			memoryAllocated.modelGroups[i].vertPosition = malloc(sizeof(Vector3) * memoryAllocated.modelGroups[i].nVerts); //Allocates the memory for the array
			memoryAllocated.modelGroups[i].textureCoord = malloc(sizeof(Vector2) * memoryAllocated.modelGroups[i].nUVs); //Allocates the memory for the array
			memoryAllocated.modelGroups[i].normalData = malloc(sizeof(Vector3) * memoryAllocated.modelGroups[i].nNormals); //Allocates the memory for the array

			memoryAllocated.modelGroups[i].grpVertexIndicies = malloc(sizeof(Vector3Int) * memoryAllocated.modelGroups[i].nFaces); //Allocates the memory for the array
			memoryAllocated.modelGroups[i].grpNormalIndicies = malloc(sizeof(Vector3Int) * memoryAllocated.modelGroups[i].nFaces); //Allocates the memory for the array
			memoryAllocated.modelGroups[i].grpUVIndicies = malloc(sizeof(Vector3Int) * memoryAllocated.modelGroups[i].nFaces); //Allocates the memory for the array
		}
	}

	//ALLOCATES MEMORY FOR THE MODELS ARRAYS
	if (memoryAllocated.nVerts > 0)
	{
		memoryAllocated.vertPosition = malloc(sizeof(Vector3) * memoryAllocated.nVerts); //Allocates the memory for the array
	}

	if (memoryAllocated.nUVs > 0)
	{
		memoryAllocated.textureCoord = malloc(sizeof(Vector2) * memoryAllocated.nUVs); //Allocates the memory for the array
	}

	if (memoryAllocated.nNormals > 0)
	{
		memoryAllocated.normalData = malloc(sizeof(Vector3) * memoryAllocated.nNormals); //Allocates the memory for the array
	}

	if (memoryAllocated.nFaces > 0)
	{
		memoryAllocated.vertexPosIndicies = malloc(sizeof(Vector3Int) * memoryAllocated.nFaces); //Allocates the memory for the array
		memoryAllocated.normalIndicies = malloc(sizeof(Vector3Int) * memoryAllocated.nFaces); //Allocates the memory for the array
		memoryAllocated.textureCoordIndicies = malloc(sizeof(Vector3Int) * memoryAllocated.nFaces); //Allocates the memory for the array
	}

	rewind(inputPointer); //Resets the reading to the beggining of the file

	return(memoryAllocated);
}

void PrintOBJData(objModel inputData) //Prints OBJ Data to screen to confirm the data
{
	printf("--------------------------------------\n");
	printf("OBJ VERTEX DATA\n");
	printf("--------------------------------------\n");

	printf("\n");

	//Print Vertex data to the screen
	for (unsigned i = 0; i < inputData.nVerts; i++)
	{
		printf("%f, %f, %f\n",	inputData.vertPosition[i].x,
								inputData.vertPosition[i].y,
								inputData.vertPosition[i].z);
	}

	printf("\n");

	printf("--------------------------------------\n");
	printf("OBJ UV DATA\n");
	printf("--------------------------------------\n");

	printf("\n");

	//Print UV data to the screen
	for (unsigned i = 0; i < inputData.nUVs; i++)
	{
		printf("%f, %f\n",		inputData.textureCoord[i].x,
								inputData.textureCoord[i].y);
	}

	printf("\n");

	printf("--------------------------------------\n");
	printf("OBJ NORMAL DATA\n");
	printf("--------------------------------------\n");

	printf("\n");

	//Print Normal data to the screen
	for (unsigned i = 0; i < inputData.nNormals; i++)
	{
		printf("%f, %f, %f\n",	inputData.normalData[i].x,
								inputData.normalData[i].y,
								inputData.normalData[i].z);
	}

	printf("\n");

	printf("--------------------------------------\n");
	printf("OBJ FACE DATA\n");
	printf("--------------------------------------\n");

	printf("\n");

	//Print Face data to the screen
	for (unsigned i = 0; i < inputData.nFaces; i++)
	{
		printf("%d/%d/%d %d/%d/%d %d/%d/%d\n",	inputData.vertexPosIndicies[i].x,
												inputData.textureCoordIndicies[i].x,
												inputData.normalIndicies[i].x,
												inputData.vertexPosIndicies[i].y,
												inputData.textureCoordIndicies[i].y,
												inputData.normalIndicies[i].y,
												inputData.vertexPosIndicies[i].z,
												inputData.textureCoordIndicies[i].z,
												inputData.normalIndicies[i].z);
	}
}

void PrintOBJGroupData(objModel inputData) //Prints OBJ Group Data to screen to confirm the data
{
	if (inputData.nGroups > 0)
	{
		for (unsigned i = 0; i < inputData.nGroups; i++)
		{
			printf("--------------------------------------\n");
			printf("OBJ GROUP %d\n", i + 1);
			printf("--------------------------------------\n");

			printf("--------------------------------------\n");
			printf("OBJ VERTEX DATA\n");
			printf("--------------------------------------\n");

			printf("\n");

			//Print Vertex data to the screen
			for (unsigned z = 0; z < inputData.modelGroups[i].nVerts; z++)
			{
				printf("%f, %f, %f\n",	inputData.modelGroups[i].vertPosition[z].x,
										inputData.modelGroups[i].vertPosition[z].y,
										inputData.modelGroups[i].vertPosition[z].z);
			}

			printf("\n");

			printf("--------------------------------------\n");
			printf("OBJ UV DATA\n");
			printf("--------------------------------------\n");

			printf("\n");

			//Print UV data to the screen
			for (unsigned z = 0; z < inputData.modelGroups[i].nUVs; z++)
			{
				printf("%f, %f\n",	inputData.modelGroups[i].textureCoord[z].x,
									inputData.modelGroups[i].textureCoord[z].y);
			}

			printf("\n");

			printf("--------------------------------------\n");
			printf("OBJ NORMAL DATA\n");
			printf("--------------------------------------\n");

			printf("\n");

			//Print Normal data to the screen
			for (unsigned z = 0; z < inputData.modelGroups[i].nNormals; z++)
			{
				printf("%f, %f, %f\n",	inputData.modelGroups[i].normalData[z].x,
										inputData.modelGroups[i].normalData[z].y,
										inputData.modelGroups[i].normalData[z].z);
			}

			printf("\n");

			printf("--------------------------------------\n");
			printf("OBJ FACE DATA\n");
			printf("--------------------------------------\n");

			printf("\n");

			//Print Face data to the screen
			for (unsigned z = 0; z < inputData.modelGroups[i].nFaces; z++)
			{
				printf("%d/%d/%d %d/%d/%d %d/%d/%d\n",	inputData.modelGroups[i].grpVertexIndicies[z].x,
														inputData.modelGroups[i].grpUVIndicies[z].x,
														inputData.modelGroups[i].grpNormalIndicies[z].x,
														inputData.modelGroups[i].grpVertexIndicies[z].y,
														inputData.modelGroups[i].grpUVIndicies[z].y,
														inputData.modelGroups[i].grpNormalIndicies[z].y,
														inputData.modelGroups[i].grpVertexIndicies[z].z,
														inputData.modelGroups[i].grpUVIndicies[z].z,
														inputData.modelGroups[i].grpNormalIndicies[z].z);
			}
		}
	}
	else
		printf("ERROR: There are no groups to print from");
}