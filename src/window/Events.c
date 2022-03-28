#include "Events.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

void OnKeyDown(unsigned char key, int x, int y)
{
	ImGui_ImplGLUT_KeyboardFunc();
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
	ImGui_ImplGLUT_KeyboardUpFunc();
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
	ImGui_ImplGLUT_SpecialFunc();
}

void OnSpecialKeyUp(int key, int x, int y)
{
	ImGui_ImplGLUT_SpecialUpFunc();
}


void OnMouseButton(int button, int state, int x, int y)
{
	ImGui_ImplGLUT_MouseFunc();
}

void OnMouseMove(int x, int y)
{
	ImGui_ImplGLUT_MotionFunc();

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