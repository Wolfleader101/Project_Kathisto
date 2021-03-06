#include "Window.h"

#include "game/GameObjects/Cube.h"
#include "game/GameObjects/CubeG.h"
#include "game/GameObjects/JumpPad.h"
#include "game/GameObjects/Teleporters/Teleporters.h"

#include "game/GameObjects/GameGeometry/DebugGeo.h" //In Charge of building the Debug Geometry 
#include "game/GameObjects/Camera.h"
#include "game/GameObjects/CameraThirdPerson.h" //Includes the Third Person Camera
#include "game/GameObjects/Player.h" //Includes access to the player object

int WINDOW_WIDTH = 1750;
int WINDOW_HEIGHT = 980;

int frame = 0;
int timebase = 0;
int fps = 0;

Time time = {
	.currTime = 0,
	.prevTime = 0.0f,
	.deltaTime = 0.0f,
};

Time fixedTime = {
	.currTime = 0,
	.prevTime = 0.0f,
	.deltaTime = 0.0f,
};

GLfloat position0[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //Light is placed at infinity
GLfloat diffuse0[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //The diffuse colour of the light
GLfloat specular0[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //The specualr colour of the light

GLfloat globalAmbient[] = { 0.79020f, 0.78039f, 0.77647f, 1.0f }; //A global ambient colour to be applied across the scene

GameObjectManager gameObjectManager;

void InitialiseGameObjects()
{
	/////////////////////////////////////////////////
	//  INITIALISE MODELS
	/////////////////////////////////////////////////
	
	ObjFile bunny, barrel, level1;
	
	bunny = InitialiseObjFile();
	bunny = LoadOBJFile("assets/models/objs/tests/stanford-bunny_export.obj");

	if (bunny.nGroups == 1)
	{
		InitialiseOBJ(bunny, 1.0, 0.0, 0.0, true, (Vector3) {0.0f, 7.0f, 15.0f});
	}
	else
		if (bunny.nGroups > 1)
		{
			InitialiseOBJGroups(bunny, 1.0, 0.0, 0.0, true, (Vector3) {0.0f, 7.0f, 15.0f});
		}

	barrel = InitialiseObjFile();
	barrel = LoadOBJFile("assets/models/objs/tests/barrel_export.obj");

	if (barrel.nGroups == 1)
	{
		InitialiseOBJ(barrel, 0.0, 1.0, 0.0, true, (Vector3) { 0.0f, 2.0f, -15.0f });
	}
	else
		if (barrel.nGroups > 1)
		{
			InitialiseOBJGroups(barrel, 0.0, 1.0, 0.0, true, (Vector3) { 0.0f, 2.0f, -15.0f });
		}
	/*
	level1 = InitialiseObjFile();
	level1 = LoadOBJFile("assets/models/objs/finalGeo_GRP.obj");

	if (level1.nGroups == 1)
	{
		InitialiseOBJ(level1, 0.0, 1.0, 0.0, true, (Vector3) { 0.0f, 2.0f, -15.0f });
	}
	else
		if (level1.nGroups > 1)
		{
			InitialiseOBJGroups(level1, 0.0, 1.0, 0.0, true, (Vector3) { 0.0f, 2.0f, -15.0f });
		}*/

	/////////////////////////////////////////////////
	//  INITIALISE BUILT-IN GAME OBJECTS
	/////////////////////////////////////////////////

	// first you must initialise your gameobjects
	GameObject* cube = malloc(sizeof(GameObject));
	GameObject* cubeG = malloc(sizeof(GameObject));
	GameObject* playerObject = malloc(sizeof(GameObject));
	GameObject* jumpPad = malloc(sizeof(GameObject));
	GameObject* Teleporter1 = malloc(sizeof(GameObject));
	GameObject* Teleporter2 = malloc(sizeof(GameObject));

	InitGameObject(cube);
	InitGameObject(cubeG);
	InitGameObject(playerObject);
	InitGameObject(jumpPad);
	InitGameObject(Teleporter1);
	InitGameObject(Teleporter2);

	// setup their callbacks, start should never be NULL, however the others can be
	SetupCallbacks(cube, OnCubeStart, OnCubeUpdate, NULL, OnCubeFixedUpdate, OnCubeCollision);
	SetupCallbacks(cubeG, OnCubeGStart, NULL, NULL, NULL, NULL);
	SetupCallbacks(playerObject, OnPlayerStart, NULL, NULL, OnPlayerFixedUpdate, OnPlayerCollision);
	SetupCallbacks(jumpPad, OnJumpPadStart, OnJumpPadUpdate, NULL, OnJumpPadFixedUpdate, OnJumpPadCollision);
	SetupCallbacks(Teleporter1, OnTeleporter1Start, OnTeleporter1Update, NULL, NULL, OnTeleporter1Collision);
	SetupCallbacks(Teleporter2, OnTeleporter2Start, NULL, NULL, NULL, OnTeleporter2Collision);

	// add them to the game object manager where start will be called
	GameObjectManagerAdd(&gameObjectManager, cube);
	GameObjectManagerAdd(&gameObjectManager, cubeG);
	GameObjectManagerAdd(&gameObjectManager, playerObject);
	GameObjectManagerAdd(&gameObjectManager, jumpPad);
	GameObjectManagerAdd(&gameObjectManager, Teleporter1);
	GameObjectManagerAdd(&gameObjectManager, Teleporter2);

	//Builds the default Debug Geometry
	BuildDebugGeo(&gameObjectManager);

	//Sets the objects needed for the camera
	SetCamAttributes(&gameObjectManager);
}

void InitialiseOBJ(ObjFile inputOBJ, float r, float g, float b, bool uniformColour, Vector3 transformPosition)
{
	GameObject* inputObject = calloc(1, sizeof(GameObject));

	if (inputObject == NULL) return;

	InitGameObject(inputObject);

	inputObject->name = calloc(25, sizeof(char));
	if (inputObject->name != NULL)
	{
		strcpy(inputObject->name, "Lucy");
	}

	objToMesh(inputOBJ.modelGroups[0], &inputObject->mesh);

	inputObject->mesh.colors = calloc(1, sizeof(RGBA));

	if (inputObject->mesh.colors != NULL) inputObject->mesh.colors[0] = (RGBA){ r, g, b, 1.0f };
	if (uniformColour)
	{
		inputObject->mesh.isUniformColor = true;
	}
	else
		inputObject->mesh.isUniformColor = false;

	inputObject->rigidBody.isStatic = true;
	inputObject->rigidBody.useGravity = false;

	inputObject->transform.position = transformPosition; //Sets initial position (Transform) of mesh

	GameObjectManagerAdd(&gameObjectManager, inputObject);
}

void InitialiseOBJGroups(ObjFile inputOBJ, float r, float g, float b, bool uniformColour, Vector3 transformPosition)
{
	for (size_t i = 0; i < inputOBJ.nGroups; i++)
	{
		GameObject* go = calloc(1, sizeof(GameObject));

		if (go == NULL) return;

		InitGameObject(go);

		go->name = calloc(25, sizeof(char));
		if (go->name != NULL)
		{
			strcpy(go->name, "Obj Object");

			char buffer[5] = "";
			itoa(i, buffer, 10);
			strcat(go->name, buffer);
		}

		objToMesh(inputOBJ.modelGroups[i], &go->mesh);

		go->mesh.colors = calloc(1, sizeof(RGBA));

		if (go->mesh.colors != NULL) go->mesh.colors[0] = (RGBA){ r, g, b, 1.0f };
		if (uniformColour)
		{
			go->mesh.isUniformColor = true;
		}
		else
			go->mesh.isUniformColor = false;

		go->rigidBody.isStatic = true;
		go->rigidBody.useGravity = false;

		go->transform.position = transformPosition; //Sets initial position (Transform) of mesh

		GameObjectManagerAdd(&gameObjectManager, go);
	}
}

void InitialiseWindow(int* argc, char** argv, char* windowName)
{
	/////////////////////////////////////////////////
	//  INITIALISE GAME FUNCTIONS & VARIABLES
	/////////////////////////////////////////////////

	// SETUP GAME OBJECT MANAGER \\
	// 
	// setup game object manager
	InitGameObjectManager(&gameObjectManager);

	InitialiseGameObjects();

	// initialise GLUT, with debug logs
	glutInit(argc, argv);
	glutInitContextFlags(GLUT_DEBUG);

	// set RGBA mode, double buffer window, and have a depth buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// set the window starting position and size
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// set window name
	glutCreateWindow(windowName);

	// Initialise the GUI
	GuiInit();

	// callback functions

	// on reshape
	glutReshapeFunc(ReshapeWindow);

	// rendering callbacks
	glutDisplayFunc(WindowRender);
	glutIdleFunc(WindowRender);

	// keyboard and mouse input
	glutKeyboardFunc(OnKeyDown); // on key down
	glutKeyboardUpFunc(OnKeyUp); // on key up

	glutSpecialFunc(OnSpecialKeyDown); // on special key down (function keys, ctrl etc)
	glutSpecialUpFunc(OnSpecialKeyUp); // on special key up

	glutIgnoreKeyRepeat(1); // ignore auto repeat keystrokes so it doesnt constantly fire key up and key down

	glutMouseFunc(OnMouseButton); // on mouse click
	glutPassiveMotionFunc(OnMouseMove); // ALWAYS MOVING

	//glutFullScreen();

	// hide the cursor
	glutSetCursor(GLUT_CURSOR_NONE);
  
	/////////////////////////////////////////////////
	//  INITIALISE LIGHTING TO DEFAULT VALUES
	/////////////////////////////////////////////////

	glEnable(GL_LIGHTING); //Enable Lighting

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient); //Applies a global ambient colour
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //Changes the lighting mode to a local viewport

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0); //Set the diffuse colour for light 0
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0); //Set the specular colour for light 0
	glLightfv(GL_LIGHT0, GL_POSITION, position0); //Set the position of light 0

	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f); //How concentrated the light is (Default is 0)

	UpdateSunlight((float[]) { -1.0f, -1.0f, 0.0f }, 90.0f);

	glEnable(GL_LIGHT0); //Enable light 0

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// fixed update
	glutTimerFunc(PHYSICS_TIME_STEP, FixedUpdate, 0);
  
	// enter loop
	glutMainLoop();

	// on program close
	GuiFree();
}

void UpdateSunlight(float sunDir[3], float sunCutoff)
{
	//Sun direction
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, sunDir); //Updates the direction of the spotlight which represents the sun

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, sunCutoff); //Updates the cone of the spotlight which represents the sun
}

void WindowRender(void)
{
	if (EXIT_PROGRAM) return;

	// calculate delta time (time since last frame)
	CalculateTime();

	GuiUpdate(&gameObjectManager);

	glClearColor(0.52941f, 0.80784f, 0.92157f, 1.0f);

	// clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// resets transformations
	glLoadIdentity();

	// CAMERA RENDER
	if (FREE_CAM == false)
	{
		ThirdPersonCamRender(time);
	}
	else
		CameraRender(time.deltaTime);

	// ======= GAME OBJECTS RENDER  ======= \\
		
	UpdateGameObjects(time, &gameObjectManager);

	// ======================================= \\

	GuiRender();

	// swap the buffers
	glutSwapBuffers();
}

void FixedUpdate(int val)
{
	if (EXIT_PROGRAM) return;

	// setup the next tick
	glutTimerFunc(PHYSICS_TIME_STEP, FixedUpdate, 0);

	CalculateFixedTime();

	if(!PAUSE_PHYSICS) FixedUpdateGameObjects(fixedTime, &gameObjectManager);
}

void CalculateTime()
{
	// get the current delta time (time since last frame)
	time.currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	time.deltaTime = (time.currTime - time.prevTime);
	time.prevTime = time.currTime;
}

void CalculateFixedTime()
{
	fixedTime.currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	fixedTime.deltaTime = (fixedTime.currTime - fixedTime.prevTime);
	fixedTime.prevTime = fixedTime.currTime;
}

void ReshapeWindow(int width, int height)
{
	ImGui_ImplGLUT_ReshapeFunc(width, height);
	// if height is 0 then set it 1
	if (height == 0) height = 1;

	// set the window width and height
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;

	// get the width:height ratio
	float ratio = width * 1.0f / height;

	// set the matrix to projection
	glMatrixMode(GL_PROJECTION);

	// reset transformations
	glLoadIdentity();

	// set the viewports width and height
	glViewport(0, 0, width, height);

	// set the perspective for the projection matrix
	// fov, aspect ratio, near clipping distance, far clipping distance
	gluPerspective(45, ratio, 1, 500);

	// set the matrix mode back to model view
	glMatrixMode(GL_MODELVIEW);
}