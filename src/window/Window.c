#include "Window.h"

#include "game/GameObjects/Cube.h"
#include "game/GameObjects/CubeG.h"
#include "game/GameObjects/JumpPad.h"
#include "game/GameObjects/Teleporters/Teleporters.h"

#include "game/GameObjects/GameGeometry/DebugGeo.h" //In Charge of building the Debug Geometry 
#include "game/GameObjects/GameGeometry/Monkey.h" 
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
	//  LOAD OBJ FILES
	/////////////////////////////////////////////////

	objModel objData;

	objData = InitialiseData("assets/models/objs/finalGeo_GRP.obj");
	objData = LoadOBJFile("assets/models/objs/finalGeo_GRP.obj");

	//PrintOBJData(objData); //Prints the data of the entire model

	PrintOBJGroupData(objData); //Prints the group data from the model

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
	//GameObject* monkey = malloc(sizeof(GameObject));

	InitGameObject(cube);
	InitGameObject(cubeG);
	InitGameObject(playerObject);
	InitGameObject(jumpPad);
	InitGameObject(Teleporter1);
	InitGameObject(Teleporter2);
	//InitGameObject(monkey);

	// setup their callbacks, start should never be NULL, however the others can be
	SetupCallbacks(cube, OnCubeStart, OnCubeUpdate, NULL, OnCubeFixedUpdate, OnCubeCollision);
	SetupCallbacks(cubeG, OnCubeGStart, NULL, NULL, NULL, NULL);
	SetupCallbacks(playerObject, OnPlayerStart, NULL, NULL, OnPlayerFixedUpdate, OnPlayerCollision);
	SetupCallbacks(jumpPad, OnJumpPadStart, OnJumpPadUpdate, NULL, OnJumpPadFixedUpdate, OnJumpPadCollision);
	SetupCallbacks(Teleporter1, OnTeleporter1Start, OnTeleporter1Update, NULL, NULL, OnTeleporter1Collision);
	SetupCallbacks(Teleporter2, OnTeleporter2Start, NULL, NULL, NULL, OnTeleporter2Collision);
	
	//SetupCallbacks(monkey, OnMonkeyStart, NULL, NULL, NULL, NULL);


	// add them to the game object manager where start will be called
	GameObjectManagerAdd(&gameObjectManager, cube);
	GameObjectManagerAdd(&gameObjectManager, cubeG);
	GameObjectManagerAdd(&gameObjectManager, playerObject);
	GameObjectManagerAdd(&gameObjectManager, jumpPad);
	GameObjectManagerAdd(&gameObjectManager, Teleporter1);
	GameObjectManagerAdd(&gameObjectManager, Teleporter2);


	//GameObjectManagerAdd(&gameObjectManager, monkey);

	//Sets the objects needed for the camera
	SetCamAttributes(&gameObjectManager);

	BuildDebugGeo(&gameObjectManager); //Builds Debug Geometry

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