#include "Application.h"
#include <iostream>

#include "Renderer/Renderer.h"
#include "Events/EventSystem.h"
#include "Core/ModuleSystem/ModuleSystem.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace std;

Application::Application()
{
	pInstance = this;
	// Glfw init ===================================================================
	if (!glfwInit())
	{
		cerr << "Failed to initialize GLFW!" << endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// FullScreen ============
	// glfwWindowHint(GLFW_DECORATED, 0);
	// const GLFWvidmode* mode = glfwGetVideoMode(PrimaryMonitor);
	// Width = mode->width;
	// Height = mode->height;
	// ========================

	GameWindow = glfwCreateWindow(Width, Height, "ProjectA_3D", nullptr, nullptr);
	if (!GameWindow)
	{
		cerr << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(GameWindow);

	glfwSetInputMode(GameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Glew init ======================================================================
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initialize GLEW!" << endl;
		glfwTerminate();
		return;
	}

	glViewport(0, 0, Width, Height);

	// ImGui ==========================================================================

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(GameWindow, false);
	ImGui_ImplOpenGL3_Init("#version 450");

	// Core components ================================================================
	pEventSystem = new EventSystem;
	pRenderer = new Renderer;
	pModuleSystem = new ModuleSystem;

	Run();
}

Application::~Application()
{
	cout << "Application destroyed" << endl;
	delete pModuleSystem;
	delete pEventSystem;
	delete pRenderer;
	glfwTerminate();
}

void Application::SetWindowSize(const int InWidth, const int InHeight)
{
	Width = InWidth;
	Height = InHeight;
	glViewport(0, 0, Width, Height);
	onUpdateWindowSize(Width, Height);
}

void Application::Run()
{
	while (!glfwWindowShouldClose(GameWindow))
	{
		pEventSystem->Update();
		pRenderer->Draw();
		pModuleSystem->Tick();
		glfwSwapBuffers(GameWindow);
	}
}

void Application::CloseWindow()
{
	glfwSetWindowShouldClose(GameWindow, GL_TRUE);
}
