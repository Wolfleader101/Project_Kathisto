#include "objLoader.h"

objModel InitialiseData() //Used to initialise the data within an OBJ Model
{
	objModel initialisedData; //Data to be passed back

	//Initialises the amounts of faces, normals, uvs and verts to 0
	initialisedData.nFaces = 0;
	initialisedData.nNormals = 0;
	initialisedData.nUVs = 0;
	initialisedData.nVerts = 0;

	//Initialises the vectors for the model data
	Vec3_InitialiseList(&initialisedData.vertPosition);
	Vec2_InitialiseList(&initialisedData.textureCoord);
	Vec3_InitialiseList(&initialisedData.normalData);

	//Initialises the vectors for the face indicies
	Vec3Int_InitialiseList(&initialisedData.vertexPosIndicies);
	Vec3Int_InitialiseList(&initialisedData.normalIndicies);
	Vec3Int_InitialiseList(&initialisedData.textureCoordIndicies);

	return(initialisedData); //Return initialised data
}

objModel LoadOBJFile(const char* filePath) //Load and return the data for an OBJ File
{
	FILE* filePointer = NULL; //File pointer to OBJ File
	int lineResult; //Checks the results of an fscanf of a line
	
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

	while(1) //Loops while not equal to the End of File (EOF)
	{
		char lineBuffer[128]; //Each line of the file is read into the buffer

		int lineResult = fscanf(filePointer, "%s", lineBuffer); //Reads the first word of the line

		if(lineResult == EOF) //Checks to see if the result of the line read is an End of File (EOF)
		{
			break; //Breaks from the loop of End of File (EOF) is reached
		}

		if(strcmp(lineBuffer, "v") == 0) //Checks to see if the line contains 'v' (Vertex)
		{
			fscanf(filePointer, "%f %f %f\n", &vec3_tmpData1.x, &vec3_tmpData1.y, &vec3_tmpData1.z); //Reads data into temporary container

			Vec3_AddToList(&objData.vertPosition, vec3_tmpData1); //Adds to the list

			objData.nVerts++; //Adds one count to the number of verticies
		}

		if(strcmp(lineBuffer, "vt") == 0) //Checks to see if the line contains 'vt' (Vertex Texture)
		{
			fscanf(filePointer, "%f %f\n", &vec2_tmpData1.x, &vec2_tmpData1.y); //Reads data into temporary container

			Vec2_AddToList(&objData.textureCoord, vec2_tmpData1); //Adds to the list

			objData.nUVs++; //Adds one count to the number of UVs
		}

		if(strcmp(lineBuffer, "vn") == 0) //Checks to see if the line contains 'vn' (Vertex Normal)
		{
			fscanf(filePointer, "%f %f %f\n", &vec3_tmpData1.x, &vec3_tmpData1.y, &vec3_tmpData1.z); //Reads data into temporary container

			Vec3_AddToList(&objData.normalData, vec3_tmpData1); //Adds to the list

			objData.nNormals++; //Adds one count to the number of normals
		}

		if (strcmp(lineBuffer, "f") == 0) //Checks to see if the line contains 'f' (Face)
		{
			int vertsInFace = fscanf(filePointer, "%d/%d/%d %d/%d/%d %d/%d/%d\n",	&vec3Int_tmpData1.x, &vec3Int_tmpData2.x, &vec3Int_tmpData3.x,	//Vertex Index 1 | UV Index 1 | Normal Index 1
																					&vec3Int_tmpData1.y, &vec3Int_tmpData2.y, &vec3Int_tmpData3.y,	//Vertex Index 2 | UV Index 2 | Normal Index 2
																					&vec3Int_tmpData1.z, &vec3Int_tmpData2.z, &vec3Int_tmpData3.z);	//Vertex Index 3 | UV Index 3 | Normal Index 3

			vec3Int_tmpData1.x -= 1;
			vec3Int_tmpData1.y -= 1;
			vec3Int_tmpData1.z -= 1;
			vertsInFace /= 3; //Converts it into the number of vertexes (3 = Triangles, 4 = Quads, etc.)

			if(vertsInFace != 3) //Checks to see if the file is triangulated
			{
				printf("ERROR: File is not triangulated! Please edit the file and triangulate all faces!\n");

				exit(0);
			}

			Vec3Int_AddToList(&objData.vertexPosIndicies, vec3Int_tmpData1); //Adds to the list
			Vec3Int_AddToList(&objData.textureCoordIndicies, vec3Int_tmpData2); //Adds to the list
			Vec3Int_AddToList(&objData.normalIndicies, vec3Int_tmpData3); //Adds to the list

			objData.nFaces++; //Adds one count to the number of faces
		}
	}

	fclose(filePointer); //Closes the file

	return(objData); //Return data
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
		printf("%f, %f, %f\n",	Vec3_GetFromListIndex(&inputData.vertPosition, i).x,
								Vec3_GetFromListIndex(&inputData.vertPosition, i).y,
								Vec3_GetFromListIndex(&inputData.vertPosition, i).z);
	}

	printf("\n");

	printf("--------------------------------------\n");
	printf("OBJ UV DATA\n");
	printf("--------------------------------------\n");

	printf("\n");

	//Print UV data to the screen
	for (unsigned i = 0; i < inputData.nUVs; i++)
	{
		printf("%f, %f\n",		Vec2_GetFromListIndex(&inputData.textureCoord, i).x,
								Vec2_GetFromListIndex(&inputData.textureCoord, i).y);
	}

	printf("\n");

	printf("--------------------------------------\n");
	printf("OBJ NORMAL DATA\n");
	printf("--------------------------------------\n");

	printf("\n");

	//Print Normal data to the screen
	for (unsigned i = 0; i < inputData.nNormals; i++)
	{
		printf("%f, %f, %f\n",	Vec3_GetFromListIndex(&inputData.normalData, i).x,
								Vec3_GetFromListIndex(&inputData.normalData, i).y,
								Vec3_GetFromListIndex(&inputData.normalData, i).z);
	}

	printf("\n");

	printf("--------------------------------------\n");
	printf("OBJ FACE DATA\n");
	printf("--------------------------------------\n");

	printf("\n");

	//Print Face data to the screen
	for (unsigned i = 0; i < inputData.nFaces; i++)
	{
		printf("%d/%d/%d %d/%d/%d %d/%d/%d\n",	Vec3Int_GetFromListIndex(&inputData.vertexPosIndicies, i).x,
												Vec3Int_GetFromListIndex(&inputData.textureCoordIndicies, i).x,
												Vec3Int_GetFromListIndex(&inputData.normalIndicies, i).x,
												Vec3Int_GetFromListIndex(&inputData.vertexPosIndicies, i).y,
												Vec3Int_GetFromListIndex(&inputData.textureCoordIndicies, i).y,
												Vec3Int_GetFromListIndex(&inputData.normalIndicies, i).y,
												Vec3Int_GetFromListIndex(&inputData.vertexPosIndicies, i).z,
												Vec3Int_GetFromListIndex(&inputData.textureCoordIndicies, i).z,
												Vec3Int_GetFromListIndex(&inputData.normalIndicies, i).z);
	}
}