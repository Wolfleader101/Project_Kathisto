#include "Gui.h"

struct ImGuiContext* ctx;
struct ImGuiIO* io;
float test = 1.0f;

void GuiInit()
{
	ctx = igCreateContext(NULL); // create context with default font (NULL)
	io = igGetIO(); // get IO

	  //set docking
	//io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

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

	igText("F3 - Toggle between ingame/settings cursor");
	igText("F4 - Toggle debug menu");

	for (size_t i = 0; i <= gameObjectManager->lastIndex; i++)
	{
		if (gameObjectManager->gameObjects[i].name != NULL)
		{
			GameObjectPanel(&gameObjectManager->gameObjects[i]);
		}
	}
	igEnd();
}

void GuiUpdate(GameObjectManager* gameObjectManager)
{
	ImGui_ImplOpenGL2_NewFrame(); // call imgui opengl 2 new frame
	ImGui_ImplGLUT_NewFrame(); // call imgui GLUT new frame

	if (TOGGLE_MENU) DebugMenu(gameObjectManager); // draw debug menu
}

void GuiRender()
{
	igRender(); // call imgui render
	ImGui_ImplOpenGL2_RenderDrawData(igGetDrawData()); // call opengl2 render
}

void GameObjectPanel(GameObject* gameObject)
{
	if (igCollapsingHeader_TreeNodeFlags(gameObject->name, ImGuiTreeNodeFlags_CollapsingHeader))
	{
		igPushStyleColor_Vec4(ImGuiCol_Button, (ImVec4) { 0.45f, 0.0f, 0.0f, 1.0f });
		igPushStyleColor_Vec4(ImGuiCol_ButtonHovered, (ImVec4) { 0.6f, 0.0f, 0.0f, 1.0f });
		igPushStyleColor_Vec4(ImGuiCol_ButtonActive, (ImVec4) { 1.0f, 0.0f, 0.0f, 1.0f });
		if (igButton("Delete", (ImVec2) { 60.0f, 20.0f }))
		{
			GameObjectManagerRemove(&gameObjectManager, gameObject->id);
		}
		igPopStyleColor(3);
		igCheckbox("Debug", &gameObject->debug);
		TransformWidget(&gameObject->transform);
		RigidBodyWidget(&gameObject->rigidBody);
		MeshWidget(&gameObject->mesh);
		igSeparator();
	}

}
void TransformWidget(Transform* transform)
{
	if (igCollapsingHeader_TreeNodeFlags("Transform", ImGuiTreeNodeFlags_CollapsingHeader))
	{
		igInputFloat3("Position", &transform->position, "%.02f", ImGuiInputTextFlags_None);
		igInputFloat3("Rotation", &transform->rotation, "%.02f", ImGuiInputTextFlags_None);
		igInputFloat3("Scale", &transform->scale, "%.02f", ImGuiInputTextFlags_None);
		igTreePop();
		igSeparator();
	}
}
void RigidBodyWidget(RigidBody* rigidBody)
{

}
void MeshWidget(Mesh* mesh)
{

}
