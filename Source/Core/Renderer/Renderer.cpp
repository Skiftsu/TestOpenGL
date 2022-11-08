#include "Renderer.h"
#include <iostream>
#include "Camera.h"

using namespace std;
using namespace glm;

Renderer::Renderer()
{
	glClearColor(0.82f, 0.81f, 0.88f, 1.f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	/* Image alpha */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	pCamera = new Camera(vec3(0), radians(90.f));
}

Renderer::~Renderer()
{
	delete pCamera;
}

void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float CurrentTime = glfwGetTime();

	static float LastTime = static_cast<float>(glfwGetTime());
	DeltaTime = CurrentTime - LastTime;
	LastTime = CurrentTime;
}