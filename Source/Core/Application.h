#pragma once
#include "Core/GL.h"
#include "callbacklist.h"

struct GLFWwindow;
class Renderer;
class EventSystem;
class ModuleSystem;

class Application
{
	// Window
	GLint Width = 1280;
	GLint Height = 720;

	GLFWwindow* GameWindow;
	Renderer* pRenderer;
	EventSystem* pEventSystem;
	ModuleSystem* pModuleSystem;

	static inline Application* pInstance;

public:
	static Application* GetInstance() { return pInstance; };

	eventpp::CallbackList<void(int OutWidth, int OutHeight)> onUpdateWindowSize;
	Application();
	Application(const Application&) = delete;
	~Application();

	GLFWwindow* GetGameWindow() { return GameWindow; };
	inline void GetWindowSize(int& OutWidth, int& OutHeight)
	{
		OutWidth = Width;
		OutHeight = Height;
	};

	void Run();
	void CloseWindow();
	void SetWindowSize(const int Width, const int Height);
};
