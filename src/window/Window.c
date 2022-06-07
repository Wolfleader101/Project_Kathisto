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


GameObjectManager gameObjectManager;


void InitialiseWindow(int* argc, char** argv, char* windowName)
{
	/////////////////////////////////////////////////
	//  INITIALISE GAME FUNCTIONS & VARIABLES
	/////////////////////////////////////////////////

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

	// fixed update
	glutTimerFunc(PHYSICS_TIME_STEP, FixedUpdate, 0);

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

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// SETUP GAME OBJECT MANAGER \\
	// 
	// setup game object manager
	InitGameObjectManager(&gameObjectManager);

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

	//Sets the objects needed for the camera
	SetCamAttributes(&gameObjectManager);

	ObjFile objFile;

	objFile = InitialiseObjFile();
	objFile = LoadOBJFile("assets/models/objs/finalGeo_GRP.obj");

	GameObject* objObjects = calloc(objFile.nGroups, sizeof(GameObject));

	for (size_t i = 0; i < objFile.nGroups && objObjects != NULL; i++)
	{
		GameObject* go = calloc(1, sizeof(GameObject));

		if (go == NULL) return;

		InitGameObject(go);


		objObjects[i] = *go;


		char name[20] = "World Object ";
		char buffer[5] = "";
		itoa(i, buffer, 10);
		strcat(name, buffer);
		objObjects[i].name = calloc(25, sizeof(char));
		if (objObjects[i].name != NULL)
			strcpy(objObjects[i].name, name);

		objToMesh(objFile.modelGroups[i], &objObjects[i].mesh);
		objObjects[i].rigidBody.isStatic = true;
		float r, g, b;
		if ((i / 3) % 2 == 0)
		{
			r = g = b = 0.611;
		}
		else {
			r = g = b = 0.360;
		}

		objObjects[i].mesh.colors = calloc(1, sizeof(RGBA));
		if (objObjects[i].mesh.colors != NULL)
			objObjects[i].mesh.colors[0] = (RGBA){ r, g, b, 1.0f };
		objObjects[i].mesh.isUniformColor = true;
		objObjects->rigidBody.debug = true;

		GameObjectManagerAdd(&gameObjectManager, &objObjects[i]);
	}

	//BuildDebugGeo(&gameObjectManager); //Builds Debug Geometry

	// enter loop
	glutMainLoop();

	// on program close
	GuiFree();
}

void WindowRender(void)
{
	if (EXIT_PROGRAM) return;

	// calculate delta time (time since last frame)
	CalculateTime();

	GuiUpdate(&gameObjectManager);

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

	FixedUpdateGameObjects(fixedTime, &gameObjectManager);
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