#include "Events.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

bool USE_MENU_CURSOR = false;
bool TOGGLE_MENU = true;

void OnKeyDown(unsigned char key, int x, int y)
{
	ImGui_ImplGLUT_KeyboardFunc(key, x, y);
	switch (key) {
	case 'w':
		cameraMoveDir.z = 1.0f;
		break;
	case 'a':
		cameraMoveDir.x = -1.0f;
		break;
	case 's':
		cameraMoveDir.z = -1.0f;
		break;
	case 'd':
		cameraMoveDir.x = 1.0f;
		break;
	case ' ':
		cameraMoveDir.y = 1.0f;
		break;
	case 'z':
		cameraMoveDir.y = -1.0f;
		break;
	case 27:
		exit(0);
		break;
	}
}

void OnKeyUp(unsigned char key, int x, int y)
{
	ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
	switch (key) {
	case 'w':
		cameraMoveDir.z = 0.0f;
		break;
	case 'a':
		cameraMoveDir.x = 0.0f;
		break;
	case 's':
		cameraMoveDir.z = 0.0f;
		break;
	case 'd':
		cameraMoveDir.x = 0.0f;
		break;
	case ' ':
		cameraMoveDir.y = 0.0f;
		break;
	case 'z':
		cameraMoveDir.y = 0.0f;
		break;
	}
}


void OnSpecialKeyDown(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F3:
		USE_MENU_CURSOR = !USE_MENU_CURSOR;
		break;
	case GLUT_KEY_F4:
		TOGGLE_MENU = !TOGGLE_MENU;
		break;
	}
}

void OnSpecialKeyUp(int key, int x, int y)
{
	ImGui_ImplGLUT_SpecialUpFunc(key, x ,y);
}


void OnMouseButton(int button, int state, int x, int y)
{
	ImGui_ImplGLUT_MouseFunc(button, state, x, y);
}

void OnMouseMove(int x, int y)
{
	ImGui_ImplGLUT_MotionFunc(x, y);

	// if they are using the debug menu show cursor and dont move camera
	if (USE_MENU_CURSOR) {
		// show the cursor
		glutSetCursor(GLUT_CURSOR_INHERIT);
		return;
	}

	//otherwise set the cursor to none
	glutSetCursor(GLUT_CURSOR_NONE);

	glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2);

	// update mouse deltas
	mouseDeltaPos.x = (x - (WINDOW_WIDTH / 2)) * MOUSE_SENS;
	mouseDeltaPos.y = (y - (WINDOW_WIDTH / 2)) * MOUSE_SENS;

	// update camera's direction
	cameraForwardDir.x = sin(mousePos.x + mouseDeltaPos.x);  // left/right
	cameraForwardDir.y = -tan(mousePos.y + mouseDeltaPos.y); // up/down
	cameraForwardDir.z = -cos(mousePos.x + mouseDeltaPos.x); // forward/back

	// increase the mouse pos by the delta mouse pos
	mousePos.x += mouseDeltaPos.x;
	mousePos.y += mouseDeltaPos.y;

}