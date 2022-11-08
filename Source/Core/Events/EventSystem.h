#pragma once

#include "Core/GL.h"
#include <callbacklist.h>
#include <glm.hpp>
#include "InputTypes.h"

class EventSystem
{
	GLuint* KeysState;
	bool CursorStarted, CursorLocked;

	static inline EventSystem* pEventSystem;
	static void KeyCallback(GLFWwindow*, int, int, int, int);
	void KeyCallbackImpl(GLFWwindow* Window, int Key, int Scancode, int Action, int Mode);
	static void MouseButtonCallback(GLFWwindow*, int, int, int);
	void MouseButtonCallbackImpl(GLFWwindow* Window, int Button, int Action, int Mode);
	static void CursorPositionCallback(GLFWwindow*, double, double);
	void CursorPositionCallbackImpl(GLFWwindow* Window, double PosX, double PosY);

public:
	static EventSystem* GetEventSystem() { return pEventSystem; };
	eventpp::CallbackList<void(const EKey Key, const EKeyState Action)> onKeyButtonDown;
	eventpp::CallbackList<void(const double PosX, const double PosY)> onCursorMoved;
	eventpp::CallbackList<void(const EMouseButton Button, const EKeyState Action)> onMouseButtonDown;

	EventSystem();
	~EventSystem();
	void Update();

	bool isPressed(int KeyCode, bool Mouse = false);
};
