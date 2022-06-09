#include "Gui.h"

struct ImGuiContext* ctx;
struct ImGuiIO* io;
bool collidersActivatedOnce = false;
bool collidersDeActivatedOnce = false;


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

void ToggleColliderView()
{
	if (SHOW_COLLIDERS)
	{
		for (size_t i = 0; i < gameObjectManager.lastIndex; i++)
		{
			GameObject* gameObject = gameObjectManager.gameObjects[i];

			gameObject->mesh.disableMesh = true;
			gameObject->rigidBody.debug = true;
		}

	}
	else {
		for (size_t i = 0; i < gameObjectManager.lastIndex; i++)
		{
			GameObject* gameObject = gameObjectManager.gameObjects[i];

			gameObject->mesh.disableMesh = false;
			gameObject->rigidBody.debug = false;
		}
	}

}

void DebugMenu(GameObjectManager* gameObjectManager)
{
	igBegin("Debug Menu", NULL, 0);

	igText("F3 - Toggle between ingame/settings cursor");
	igText("F4 - Toggle debug menu");
	igText("F5 - Toggle Freecam/Thirdperson");

	if (igCollapsingHeader_TreeNodeFlags("Player Settings", ImGuiTreeNodeFlags_CollapsingHeader))
	{
		igCheckbox("Toggle Freecam", &FREE_CAM);

		igSliderFloat("Mouse Sensitivty", &MOUSE_SENS, 0, 0.01, "%.05f", ImGuiSliderFlags_None);


		igSliderFloat("Walk Speed", &WALK_SPEED, 0, 100, "%.02f", ImGuiSliderFlags_None);
		igSliderFloat("Freecam Speed", &FLY_SPEED, 0, 100, "%.02f", ImGuiSliderFlags_None);
		igSliderFloat("Freecam Up Speed", &UP_SPEED, 0, 100, "%.02f", ImGuiSliderFlags_None);
	}

	if (igCollapsingHeader_TreeNodeFlags("Physics Settings", ImGuiTreeNodeFlags_CollapsingHeader))
	{
		igCheckbox("Pause Physics", &PAUSE_PHYSICS);
		igCheckbox("Show all Colliders", &SHOW_COLLIDERS);

		collidersDeActivatedOnce = !SHOW_COLLIDERS && collidersActivatedOnce ? true : false;

		collidersActivatedOnce = SHOW_COLLIDERS ? true : false;

		if (collidersActivatedOnce || collidersDeActivatedOnce) ToggleColliderView();


		igInputFloat("Physics Time Step (ms)", &PHYSICS_TIME_STEP, 1, 5, "%.02f", ImGuiInputTextFlags_None);

		igSliderFloat("Air Density", &AIR_DENSITY, 0, 100, "%.02f", ImGuiSliderFlags_None);
		igSliderFloat("Gravitional Acceleration", &G_ACCELERATION, 0, 100, "%.02f", ImGuiSliderFlags_None);
	}



	if (igCollapsingHeader_TreeNodeFlags("GameObject List", ImGuiTreeNodeFlags_CollapsingHeader))
	{
		igIndent(20);

		for (size_t i = 0; i < gameObjectManager->lastIndex; i++)
		{
			if (gameObjectManager->gameObjects[i] != NULL && gameObjectManager->gameObjects[i]->name != NULL)
			{
				GameObjectPanel(gameObjectManager->gameObjects[i]);
			}
		}
		igTreePop();
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
	if (gameObject == NULL) return;

	if (igCollapsingHeader_TreeNodeFlags(gameObject->name, ImGuiTreeNodeFlags_None))
	{
		igIndent(20);
		igPushStyleColor_Vec4(ImGuiCol_Button, (ImVec4) { 0.45f, 0.0f, 0.0f, 1.0f });
		igPushStyleColor_Vec4(ImGuiCol_ButtonHovered, (ImVec4) { 0.6f, 0.0f, 0.0f, 1.0f });
		igPushStyleColor_Vec4(ImGuiCol_ButtonActive, (ImVec4) { 1.0f, 0.0f, 0.0f, 1.0f });
		if (igButton("Delete", (ImVec2) { 60.0f, 20.0f }))
		{
			GameObjectManagerRemove(&gameObjectManager, gameObject->id);
			return;
		}
		igPopStyleColor(3);
		igCheckbox("Debug", &gameObject->debug);
		TransformWidget(&gameObject->transform);
		RigidBodyWidget(&gameObject->rigidBody);
		MeshWidget(&gameObject->mesh);

		igTreePop();

	}
}
void TransformWidget(Transform* transform)
{
	if (igTreeNodeEx_Str("Transform", ImGuiTreeNodeFlags_None))
	{
		igInputFloat3("Position", &transform->position, "%.02f", ImGuiInputTextFlags_None);
		igInputFloat3("Rotation", &transform->rotation, "%.02f", ImGuiInputTextFlags_None);
		igInputFloat3("Scale", &transform->scale, "%.02f", ImGuiInputTextFlags_None);

		igTreePop();
	}
}
void RigidBodyWidget(RigidBody* rigidBody)
{
	if (igTreeNodeEx_Str("RigidBody", ImGuiTreeNodeFlags_None))
	{
		igCheckbox("Debug View", &rigidBody->debug);

		igCheckbox("Is Static Object", &rigidBody->isStatic);
		igCheckbox("Is a Floor", &rigidBody->isStatic);
		igCheckbox("Uses Gravity", &rigidBody->useGravity);
		igCheckbox("Is a Trigger", &rigidBody->isTrigger);
		igCheckbox("On Ground", &rigidBody->onGround);


		igInputFloat3("Velocity", &rigidBody->velocity, "%.02f", ImGuiInputTextFlags_None);
		igInputFloat("Mass", &rigidBody->mass, 1, 5, "%.02f", ImGuiInputTextFlags_None);

		if (igCheckbox("Is a Sphere", &rigidBody->sphereBody.isSphere))
		{
			igCheckbox("Sphere Radius", &rigidBody->sphereBody.isSphere);

		}
		else {
			igInputFloat3("Bounding Box Min", &rigidBody->boundingBox.minPos, "%.02f", ImGuiInputTextFlags_None);
			igInputFloat3("Bounding Box Max", &rigidBody->boundingBox.maxPos, "%.02f", ImGuiInputTextFlags_None);
		}

		igTreePop();
	}
}
void MeshWidget(Mesh* mesh)
{
	if (igTreeNodeEx_Str("Mesh", ImGuiTreeNodeFlags_None))
	{
		igCheckbox("Single Color", &mesh->isUniformColor);

		igInputFloat4("Diffuse", &mesh->meshDiffuse, "%.02f", ImGuiInputTextFlags_None);
		igInputFloat4("Ambiet", &mesh->meshAmbient, "%.02f", ImGuiInputTextFlags_None);
		igInputFloat4("Specular", &mesh->meshSpecular, "%.02f", ImGuiInputTextFlags_None);
		igInputFloat4("Shininess", &mesh->meshShininess, "%.02f", ImGuiInputTextFlags_None);

		igCheckbox("Debug Mesh", &mesh->debug);
		igCheckbox("Disable Mesh", &mesh->disableMesh);

		igTreePop();
	}
}
