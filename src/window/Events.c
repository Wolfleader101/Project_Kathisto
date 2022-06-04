#include "Events.h"


bool USE_MENU_CURSOR = false;
bool TOGGLE_MENU = true;

bool PLAYERFORWARD_TOGGLE = false;
bool PLAYERBACKWARD_TOGGLE = false;
bool PLAYERLEFT_TOGGLE = false;
bool PLAYERRIGHT_TOGGLE = false;

bool EXIT_PROGRAM = false;

bool FREE_CAM = false;

Vector2 mouseInputs = {0.0f, 0.0f}; //Stores Mouse Inputs

void OnKeyDown(unsigned char key, int x, int y)
{
	ImGui_ImplGLUT_KeyboardFunc(key, x, y);
	switch (key) {
	case 'w':
		if (FREE_CAM == false)
		{
			playerInput.y = 1.0f;

			PLAYERFORWARD_TOGGLE = true;
		}
		else
			cameraMoveDir.z = 1.0f;

		break;
	case 'a':
		if (FREE_CAM == false)
		{
			playerInput.x = 1.0f;

			PLAYERLEFT_TOGGLE = true;
		}
		else
			cameraMoveDir.x = -1.0f;

		break;
	case 's':
		if (FREE_CAM == false)
		{
			playerInput.y = -1.0f;

			PLAYERBACKWARD_TOGGLE = true;
		}
		else
			cameraMoveDir.z = -1.0f;

		break;
	case 'd':
		if (FREE_CAM == false)
		{
			playerInput.x = -1.0f;

			PLAYERRIGHT_TOGGLE = true;
		}
		else
			cameraMoveDir.x = 1.0f;

		break;
	case ' ':
		if (FREE_CAM == false)
		{
			return;
		}
		else
			cameraMoveDir.y = 1.0f;

		break;
	case 'z':
		if (FREE_CAM == false)
		{
			return;
		}
		else
			cameraMoveDir.y = -1.0f;

		break;
	case 27:
		if (EXIT_PROGRAM == false)
		{
			EXIT_PROGRAM = true;

			DisplayGroupPhoto("assets/images/image.jpg", 640, 622, 3, 3); //Display the group photo before exiting the program

			glutTimerFunc(3000, exit, 0); //Exits program after 3 seconds
		}

		break;
	}
}

void OnKeyUp(unsigned char key, int x, int y)
{
	ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
	switch (key) {
	case 'w':
		cameraMoveDir.z = 0.0f;

		playerInput.y = 0.0f;

		PLAYERFORWARD_TOGGLE = false;

		desiredPlayerVel.x = 0.0f;
		desiredPlayerVel.z = 0.0f;

		break;
	case 'a':
		cameraMoveDir.x = 0.0f;

		playerInput.x = 0.0f;

		PLAYERLEFT_TOGGLE = false;

		desiredPlayerVel.x = 0.0f;
		desiredPlayerVel.z = 0.0f;

		break;
	case 's':
		cameraMoveDir.z = 0.0f;

		playerInput.y = 0.0f;

		PLAYERBACKWARD_TOGGLE = false;

		desiredPlayerVel.x = 0.0f;
		desiredPlayerVel.z = 0.0f;

		break;
	case 'd':
		cameraMoveDir.x = 0.0f;

		playerInput.x = 0.0f;

		PLAYERRIGHT_TOGGLE = false;

		desiredPlayerVel.x = 0.0f;
		desiredPlayerVel.z = 0.0f;

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
	case GLUT_KEY_F5:
		if (FREE_CAM == false)
		{
			FREE_CAM = true;

			//Sets the Free Camera's variables to be equal to that of the Third Person Camera
			cameraForwardDir = camForwardDir;
			cameraPos = camPos;

			//Nulls out the player inputs
			playerInput.x = 0.0f;
			playerInput.y = 0.0f;

			//Stops the player object from being able to move
			PLAYERFORWARD_TOGGLE = false;
			PLAYERLEFT_TOGGLE = false;
			PLAYERBACKWARD_TOGGLE = false;
			PLAYERRIGHT_TOGGLE = false;

			//Sets the player's velocity to 0 so they aren't moving
			desiredPlayerVel.x = 0.0f;
			desiredPlayerVel.z = 0.0f;
		}
		else
			FREE_CAM = false;

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

	if (FREE_CAM == false) //If the free camera is not active
	{
		// increase the mouse pos by the delta mouse pos (THIRD PERSON CAMERA VARIABLES)
		mouseInputs.x = mouseDeltaPos.x;
		mouseInputs.y = mouseDeltaPos.y;
	}
	else //Update the free camera's variables
	{
		// update camera's direction
		cameraForwardDir.x = sin(mousePos.x + mouseDeltaPos.x);  // left/right
		cameraForwardDir.y = -tan(mousePos.y + mouseDeltaPos.y); // up/down
		cameraForwardDir.z = -cos(mousePos.x + mouseDeltaPos.x); // forward/back

		// increase the mouse pos by the delta mouse pos (FREE CAMERA VARIABLES)
		mousePos.x += mouseDeltaPos.x;
		mousePos.y += mouseDeltaPos.y;
	}
}

void DisplayGroupPhoto(const char* imgName, int imgWidth, int imgHeight, int channelsInFile, int numOfDesiredChannels) //Displays the group photo when exiting the program
{
	unsigned char* groupPhoto; //The image to be loaded
	bool validRasterPosition = false; //A valid position for the image to display on

	if ((numOfDesiredChannels == 3) || (numOfDesiredChannels == 4)) //Checks to see if the channels are RGB or RGBA
	{
		stbi_set_flip_vertically_on_load(true); //Flips the image to the correct vertical orientation

		groupPhoto = stbi_load(imgName, &imgWidth, &imgHeight, &channelsInFile, numOfDesiredChannels); //Loads the photo (With input channels value)
	}
	else //If neither, default to RGB
	{
		stbi_set_flip_vertically_on_load(true); //Flips the image to the correct vertical orientation

		groupPhoto = stbi_load(imgName, &imgWidth, &imgHeight, 3, 3); //Loads the photo (With default channels value)
	}

	if (!groupPhoto) //Checks to see if the image hasn't loaded
	{
		printf("ERROR: Could not load '%s', Reason: %s\n", imgName, stbi_failure_reason());
	}
	else //If the image is loaded
	{
		printf("SUCCESS: Image '%s' found! Displaying...\n", imgName);

		glGetBooleanv(GL_CURRENT_RASTER_POSITION_VALID, &validRasterPosition); //Checks to make sure the position of the image is valid

		if (validRasterPosition) //If the raster position is valid
		{
			printf("SUCCESS: Raster position is valid!\n");

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glDrawPixels(imgWidth, imgHeight - 1, GL_RGB, GL_UNSIGNED_BYTE, groupPhoto); //Draws the image to the screen (-1 to get the image into the bottom left corner)

			free(groupPhoto); //Free's the data of the image

			glutSwapBuffers();
		}
		else
			printf("ERROR: Raster position is not valid!");
	}
}