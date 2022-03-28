#include "Window.h"

#include "game/GameObjects/Cube.h"
#include "game/GameObjects/Floor.h"

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 750;

int frame = 0;
int timebase = 0;
int fps = 0;

Time time = {
	.currTime = 0,
	.prevTime = 0.0f,
	.deltaTime = 0.0f,
};


GameObjectManager gameObjectManager;


void InitialiseWindow(int* argc, char** argv, char* windowName)
{
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

	// hide the cursor
	glutSetCursor(GLUT_CURSOR_NONE);

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// SETUP GAME OBJECT MANAGER \\
	// 
	// setup game object manager
	InitGameObjectManager(&gameObjectManager);

	// first you must initialise your gameobjects
	InitGameObject(&cube);
	InitGameObject(&floorGameObject);

	// setup their callbacks, start should never be NULL, however the others can be
	SetupCallbacks(&cube, OnCubeStart, OnCubeUpdate, OnCubeFixedUpdate);
	SetupCallbacks(&floorGameObject, OnFloorStart, NULL, NULL);

	// add them to the game object manager where start will be called
	GameObjectManagerAdd(&gameObjectManager, cube);
	GameObjectManagerAdd(&gameObjectManager, floorGameObject);

	// enter loop
	glutMainLoop();

	// on program close
	GuiFree();
}

void WindowRender(void)
{

	// calculate delta time (time since last frame)
	CalculateDeltaTime();

	GuiUpdate(&gameObjectManager);

	// clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// resets transformations
	glLoadIdentity();

	// CAMERA RENDER
	CameraRender(time.deltaTime);

	// ======= GAME OBJECTS RENDER  ======= \\
	
	UpdateGameObjects(time, &gameObjectManager);

	// ======================================= \\

	GuiRender();

	// swap the buffers
	glutSwapBuffers();
}

void CalculateDeltaTime()
{
	// get the current delta time (time since last frame)
	time.currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	time.deltaTime = (time.currTime - time.prevTime);
	time.prevTime = time.currTime;
}

void ReshapeWindow(int width, int height)
{
	ImGui_ImplGLUT_ReshapeFunc();
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
