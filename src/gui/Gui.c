#include "Gui.h"

struct ImGuiContext* ctx;
struct ImGuiIO* io;
float test = 1.0f;

void GuiInit()
{
	ctx = igCreateContext(NULL); // create context with default font (NULL)
	io = igGetIO(); // get IO

	igStyleColorsDark(NULL); // set style to dark with no custom colors

	ImGui_ImplGLUT_Init(); // initialise imgui glut
	ImGui_ImplGLUT_InstallFuncs(); // install callback functions
	ImGui_ImplOpenGL2_Init(); //initialise in opengl2
}

void GuiFree()
{
	ImGui_ImplOpenGL2_Shutdown(); // shutdown imgui opengl2
	ImGui_ImplGLUT_Shutdown(); // shutdown imgui glut
	igDestroyContext(ctx); // destroy context
}

void DebugMenu(GameObjectManager* gameObjectManager)
{
	igBegin("Debug Menu", NULL, 0);
	
	for (size_t i = 0; i <= gameObjectManager->lastIndex; i++)
	{
		if (gameObjectManager->gameObjects[i].name != NULL)
		{
			igText(gameObjectManager->gameObjects[i].name);
			igDragFloat("Position Y", &gameObjectManager->gameObjects[i].transform.position.y, 0.1f, -100.0f, 100.0f, "%.02f", 0);
		}			
	}
	igEnd();
}

void GuiUpdate(GameObjectManager* gameObjectManager)
{
	ImGui_ImplOpenGL2_NewFrame(); // call imgui opengl 2 new frame
	ImGui_ImplGLUT_NewFrame(); // call imgui GLUT new frame

	DebugMenu(gameObjectManager); // draw debug menu
}

void GuiRender()
{
	igRender(); // call imgui render
	ImGui_ImplOpenGL2_RenderDrawData(igGetDrawData()); // call opengl2 render
}