#include "objLoader.h"

ObjModel InitialiseObjModel()
{
	ObjModel initialisedData; //Data to be passed back

	initialisedData.modelName = "";

	//Initialises the amounts of faces, normals, uvs and verts to 0
	initialisedData.nFaces = 0;
	initialisedData.nNormals = 0;
	initialisedData.nUVs = 0;
	initialisedData.nVerts = 0;

	//Initialises the arrays for the model data
	initialisedData.vertPosition = NULL;
	initialisedData.textureCoord = NULL;
	initialisedData.normalData = NULL;

	//Initialises the arrays for the face indicies
	initialisedData.vertexPosIndicies = NULL;
	initialisedData.normalIndicies = NULL;
	initialisedData.textureCoordIndicies = NULL;
}

ObjFile InitialiseObjFile() //Used to initialise the data within an OBJ Model
{
	ObjFile initialisedData; //Data to be passed back

	initialisedData.fileName = "";

	//Initialises the amounts of faces, normals, uvs and verts to 0
	initialisedData.nGroups = 0;

	//Initialises the arrays for the model group data
	initialisedData.modelGroups = NULL;

	return initialisedData; //Return initialised data
}

ObjFile AllocateModelMemory(FILE* inputPointer)
{
	ObjFile objFile = InitialiseObjFile();

	objFile.nGroups++;
	objFile.modelGroups = calloc(1, sizeof(ObjModel));
	if (objFile.modelGroups != NULL)
		objFile.modelGroups[0] = InitialiseObjModel();


	char lineBuffer[1024] = ""; //Each line of the file is read into the buffer

	//FINDS THE AMOUNT OF ITEMS WITHIN THE MODEL
	while (fscanf(inputPointer, "%s", lineBuffer) != EOF) //Loops while not equal to the End of File (EOF)
	{
		if (strcmp(lineBuffer, "g") == 0) //Checks to see if the line contains 'g' (Group)
		{
			objFile.nGroups++; //Adds one count to the number of groups
		}
	}

	rewind(inputPointer); //Resets the reading to the beggining of the file

	objFile.modelGroups = calloc(objFile.nGroups, sizeof(ObjModel)); //Allocates the memory for the array

	for (unsigned i = 0; i < objFile.nGroups; i++) //Initialise the number of variables
	{
		objFile.modelGroups[i] = InitialiseObjModel();
	}

	char* previousBuffer = ""; //The bufefr from the prvious line
	unsigned groupCounter = 0; //The counter which adds data to the next group
	unsigned endOfGroup = 0; //0 = Not end of group, 1 = Nearing end of group

	char currentBuffer[1024] = ""; //Each line of the file is read into the buffer
	while (fscanf(inputPointer, "%s", currentBuffer) != EOF) //Loops while not equal to the End of File (EOF)
	{
		if ((strcmp(currentBuffer, "v") == 0) && (endOfGroup > 0)) //Checks to see if the reader has moved to the next group
		{
			groupCounter++;

			endOfGroup = 0;
		}

		if (strcmp(currentBuffer, "v") == 0 && groupCounter < objFile.nGroups) //Checks to see if the line contains 'v' (Vertex)
		{
			objFile.modelGroups[groupCounter].nVerts++;
		}

		if (strcmp(currentBuffer, "vt") == 0 && groupCounter < objFile.nGroups) //Checks to see if the line contains 'vt' (Vertex Texture)
		{
			objFile.modelGroups[groupCounter].nUVs++;
		}

		if (strcmp(currentBuffer, "vn") == 0 && groupCounter < objFile.nGroups) //Checks to see if the line contains 'vn' (Vertex Normal)
		{
			objFile.modelGroups[groupCounter].nNormals++;
		}

		if (strcmp(currentBuffer, "f") == 0 && groupCounter < objFile.nGroups) //Checks to see if the line contains 'f' (Face)
		{
			objFile.modelGroups[groupCounter].nFaces++;

			endOfGroup = 1;
		}

		strcpy(previousBuffer, currentBuffer);
	}

	for (unsigned i = 0; i < objFile.nGroups; i++) //Initialise the number of variables
	{
		objFile.modelGroups[i].vertPosition = malloc(sizeof(Vector3) * objFile.modelGroups[i].nVerts); //Allocates the memory for the array
		objFile.modelGroups[i].textureCoord = malloc(sizeof(Vector2) * objFile.modelGroups[i].nUVs); //Allocates the memory for the array
		objFile.modelGroups[i].normalData = malloc(sizeof(Vector3) * objFile.modelGroups[i].nNormals); //Allocates the memory for the array

		objFile.modelGroups[i].vertexPosIndicies = malloc(sizeof(Vector3Int) * objFile.modelGroups[i].nFaces); //Allocates the memory for the array
		objFile.modelGroups[i].normalIndicies = malloc(sizeof(Vector3Int) * objFile.modelGroups[i].nFaces); //Allocates the memory for the array
		objFile.modelGroups[i].textureCoordIndicies = malloc(sizeof(Vector3Int) * objFile.modelGroups[i].nFaces); //Allocates the memory for the array
	}


	rewind(inputPointer); //Resets the reading to the beggining of the file

	return(objFile);
}

ObjFile LoadOBJFile(const char* filePath) //Load and return the data for an OBJ File
{
	FILE* filePointer = NULL; //File pointer to OBJ File
	int lineResult; //Checks the results of an fscanf of a line

	unsigned vertIndex = 0; //The counter which adds data to vertex position array
	unsigned texCoordIndex = 0; //The counter which adds data to the texture coordinate array
	unsigned normalIndex = 0; //The counter which adds data to the vertex normal array

	unsigned faceIndex = 0; //The counter which adds data to the face index arrays

	ObjFile objData = InitialiseObjFile(); //Data to be passed back (Initialise first)

	Vector3 vec3_tmpData1; //Temporary Vector3 used to store data to pass into the Lists
	Vector3Int vec3Int_tmpData1, vec3Int_tmpData2, vec3Int_tmpData3; //Temporary Vector3Int's used to store data to pass into the Lists
	Vector2 vec2_tmpData1; //Temporary Vector2 used to store data to pass into the Lists

	filePointer = fopen(filePath, "r"); //Opens the file
	if (filePointer == NULL) //Checks to see if the file has opened
	{
		perror("ERROR");

		exit(1);
	}

	objData = AllocateModelMemory(filePointer);

	char lineBuffer[1024] = ""; //Each line of the file is read into the buffer

	while (fscanf(filePointer, "%s", lineBuffer) != EOF) //Loops while not equal to the End of File (EOF)
	{

		char* previousBuffer = ""; //The bufefr from the prvious line
		unsigned groupCounter = 0; //The counter which adds data to the next group
		unsigned endOfGroup = 0; //0 = Not end of group, 1 = Nearing end of group

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

			if ((strcmp(currentBuffer, "v") == 0) && (endOfGroup > 0)) //Checks to see if the reader has moved to the next group
			{
				groupCounter++;

				vertIndex = 0; //Resets the counter for the next set
				texCoordIndex = 0; //Resets the counter for the next set
				normalIndex = 0; //Resets the counter for the next set
				faceIndex = 0; //Resets the counter for the next set

				endOfGroup = 0;
			}

			if (strcmp(currentBuffer, "v") == 0) //Checks to see if the line contains 'v' (Vertex)
			{
				fscanf(filePointer, "%f %f %f\n", &vec3_tmpData1.x, &vec3_tmpData1.y, &vec3_tmpData1.z); //Reads data into temporary container

				objData.modelGroups[groupCounter].vertPosition[vertIndex] = vec3_tmpData1; //Adds to the array

				vertIndex++;
			}

			if (strcmp(currentBuffer, "vt") == 0) //Checks to see if the line contains 'vt' (Vertex Texture)
			{
				fscanf(filePointer, "%f %f\n", &vec2_tmpData1.x, &vec2_tmpData1.y); //Reads data into temporary container

				objData.modelGroups[groupCounter].textureCoord[texCoordIndex] = vec2_tmpData1; //Adds to the array

				texCoordIndex++;
			}

			if (strcmp(currentBuffer, "vn") == 0) //Checks to see if the line contains 'vn' (Vertex Normal)
			{
				fscanf(filePointer, "%f %f %f\n", &vec3_tmpData1.x, &vec3_tmpData1.y, &vec3_tmpData1.z); //Reads data into temporary container

				objData.modelGroups[groupCounter].normalData[normalIndex] = vec3_tmpData1; //Adds to the array

				normalIndex++;
			}

			if (strcmp(currentBuffer, "f") == 0) //Checks to see if the line contains 'f' (Face)
			{
				int vertsInFace = fscanf(filePointer, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vec3Int_tmpData1.x, &vec3Int_tmpData2.x, &vec3Int_tmpData3.x,	//Vertex Index 1 | UV Index 1 | Normal Index 1
					&vec3Int_tmpData1.y, &vec3Int_tmpData2.y, &vec3Int_tmpData3.y,	//Vertex Index 2 | UV Index 2 | Normal Index 2
					&vec3Int_tmpData1.z, &vec3Int_tmpData2.z, &vec3Int_tmpData3.z);	//Vertex Index 3 | UV Index 3 | Normal Index 3

				vertsInFace /= 3; //Converts it into the number of vertexes (3 = Triangles, 4 = Quads, etc.)

				if (vertsInFace != 3) //Checks to see if the file is triangulated
				{
					printf("ERROR: File is not triangulated! Please edit the file and triangulate all faces!\n");

					exit(0);
				}

				//ADDS DATA TO GROUP
				objData.modelGroups[groupCounter].vertexPosIndicies[faceIndex] = vec3Int_tmpData1; //Adds to the array
				objData.modelGroups[groupCounter].textureCoordIndicies[faceIndex] = vec3Int_tmpData2; //Adds to the array
				objData.modelGroups[groupCounter].normalIndicies[faceIndex] = vec3Int_tmpData3; //Adds to the array

				faceIndex++;

				endOfGroup = 1;
			}

			strcpy(previousBuffer, currentBuffer);
		}

		for (unsigned i = 0; i < objData.nGroups; i++) //Loops through each group contained within the model
		{
			Vector3Int IndexOffset = FindIndexOffset(objData.modelGroups[i]); //Finds the Index Offset of a given group

			for (unsigned z = 0; z < objData.modelGroups[i].nFaces; z++) //Loops through all groups and their indexes, and applies the index offset to them
			{
				objData.modelGroups[i].vertexPosIndicies[z].x -= IndexOffset.x;
				objData.modelGroups[i].vertexPosIndicies[z].y -= IndexOffset.x;
				objData.modelGroups[i].vertexPosIndicies[z].z -= IndexOffset.x;

				objData.modelGroups[i].textureCoordIndicies[z].x -= IndexOffset.y;
				objData.modelGroups[i].textureCoordIndicies[z].y -= IndexOffset.y;
				objData.modelGroups[i].textureCoordIndicies[z].z -= IndexOffset.y;

				objData.modelGroups[i].normalIndicies[z].x -= IndexOffset.z;
				objData.modelGroups[i].normalIndicies[z].y -= IndexOffset.z;
				objData.modelGroups[i].normalIndicies[z].z -= IndexOffset.z;
			}
		}

		fclose(filePointer); //Closes the file

		return objData; //Return data
	}
}

Vector3Int FindIndexOffset(ObjModel inputData) //Finds the Index Offset of a given OBJ Group
{
	Vector3Int lowestIndex = inputData.normalIndicies[0]; //Sets the lowest index to an initial value from the input data (Lowest Vertex | Lowest UV | Lowest Normal)

	for (unsigned i = 0; i < inputData.nFaces; i++)
	{
		//SCANNING THROUGH VERTEX INDEXES
		if (inputData.vertexPosIndicies[i].x < lowestIndex.x)
			lowestIndex.x = inputData.vertexPosIndicies[i].x;

		if (inputData.vertexPosIndicies[i].y < lowestIndex.x)
			lowestIndex.x = inputData.vertexPosIndicies[i].y;

		if (inputData.vertexPosIndicies[i].z < lowestIndex.x)
			lowestIndex.x = inputData.vertexPosIndicies[i].z;

		//SCANNING THROUGH UV INDEXES
		if (inputData.textureCoordIndicies[i].x < lowestIndex.y)
			lowestIndex.y = inputData.textureCoordIndicies[i].x;

		if (inputData.textureCoordIndicies[i].y < lowestIndex.y)
			lowestIndex.y = inputData.textureCoordIndicies[i].y;

		if (inputData.textureCoordIndicies[i].z < lowestIndex.y)
			lowestIndex.y = inputData.textureCoordIndicies[i].z;

		//SCANNING THROUGH NORMAL INDEXES
		if (inputData.normalIndicies[i].x < lowestIndex.z)
			lowestIndex.z = inputData.normalIndicies[i].x;

		if (inputData.normalIndicies[i].y < lowestIndex.z)
			lowestIndex.z = inputData.normalIndicies[i].y;

		if (inputData.normalIndicies[i].z < lowestIndex.z)
			lowestIndex.z = inputData.normalIndicies[i].z;
	}

	return lowestIndex;
}

void PrintOBJData(ObjFile inputData) //Prints OBJ Data to screen to confirm the data
{
	for (unsigned i = 0; i < inputData.nGroups; i++)
	{
		printf("--------------------------------------\n");
		printf("OBJ GROUP %d\n", i + 1);
		printf("--------------------------------------\n");

		printf("--------------------------------------\n");
		printf("OBJ VERTEX DATA\n");
		printf("--------------------------------------\n");

		//Print Vertex data to the screen
		for (unsigned z = 0; z < inputData.modelGroups[i].nVerts; z++)
		{
			printf("%f, %f, %f\n", inputData.modelGroups[i].vertPosition[z].x,
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
			printf("%f, %f\n", inputData.modelGroups[i].textureCoord[z].x,
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
			printf("%f, %f, %f\n", inputData.modelGroups[i].normalData[z].x,
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
			printf("%d/%d/%d %d/%d/%d %d/%d/%d\n", inputData.modelGroups[i].vertexPosIndicies[z].x,
				inputData.modelGroups[i].textureCoordIndicies[z].x,
				inputData.modelGroups[i].normalIndicies[z].x,
				inputData.modelGroups[i].vertexPosIndicies[z].y,
				inputData.modelGroups[i].textureCoordIndicies[z].y,
				inputData.modelGroups[i].normalIndicies[z].y,
				inputData.modelGroups[i].vertexPosIndicies[z].z,
				inputData.modelGroups[i].textureCoordIndicies[z].z,
				inputData.modelGroups[i].normalIndicies[z].z);
		}
	}
}