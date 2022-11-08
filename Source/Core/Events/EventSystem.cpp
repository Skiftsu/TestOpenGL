#include "EventSystem.h"
#include <iostream>
#include "Core/Application.h"

#define _MOUSE_BUTTONS 1024

void WindowSizeCallback(GLFWwindow* Window, int Width, int Height)
{
	Application::GetInstance()->SetWindowSize(Width, Height);
}

EventSystem::EventSystem()
{
	pEventSystem = this;
	KeysState = new GLuint[1032];
	memset(KeysState, 0, 1032 * sizeof(GLuint));

	GLFWwindow* Window = Application::GetInstance()->GetGameWindow();
	glfwSetWindowUserPointer(Window, this);
	glfwSetKeyCallback(Window, KeyCallback);
	glfwSetMouseButtonCallback(Window, MouseButtonCallback);
	glfwSetCursorPosCallback(Window, CursorPositionCallback);
	glfwSetWindowSizeCallback(Window, WindowSizeCallback);
}

EventSystem::~EventSystem()
{
	delete KeysState;
}

void EventSystem::Update()
{
	glfwPollEvents();
}

bool EventSystem::isPressed(int KeyCode, bool Mouse)
{
	if (KeyCode < 0 || KeyCode > 1032) return false;
	return KeysState[Mouse ? _MOUSE_BUTTONS + KeyCode : KeyCode];
}

// Callbacks ======================================================================================
void EventSystem::KeyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mode)
{
	pEventSystem->KeyCallbackImpl(Window, Key, Scancode, Action, Mode);
}
void EventSystem::KeyCallbackImpl(GLFWwindow* Window, int Key, int Scancode, int Action, int Mode)
{
	KeysState[Key] = Action;
	onKeyButtonDown(static_cast<EKey>(Key), static_cast<EKeyState>(Action));
}

void EventSystem::MouseButtonCallback(GLFWwindow* Window, int Button, int Action, int Mode)
{
	pEventSystem->MouseButtonCallbackImpl(Window, Button, Action, Mode);
}
void EventSystem::MouseButtonCallbackImpl(GLFWwindow* Window, int Button, int Action, int Mode)
{
	KeysState[_MOUSE_BUTTONS + Button] = Action;
	onMouseButtonDown(static_cast<EMouseButton>(Button), static_cast<EKeyState>(Action));
}

void EventSystem::CursorPositionCallback(GLFWwindow* Window, double PosX, double PosY)
{
	pEventSystem->CursorPositionCallbackImpl(Window, PosX, PosY);
}
void EventSystem::CursorPositionCallbackImpl(GLFWwindow* Window, double PosX, double PosY)
{
	onCursorMoved(PosX, PosY);
}