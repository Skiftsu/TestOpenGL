#pragma once
#include <vector>
#include "Core/GL.h"
#include <glm.hpp>

class Camera;

class Renderer
{
	static inline Camera* pCamera;
	static inline float DeltaTime;

public:
	Renderer();
	Renderer(const Renderer&) = delete;
	~Renderer();

	void Draw();
	static float GetDeltaTime() { return DeltaTime; };
	static Camera* GetCamera() { return pCamera; };
};
