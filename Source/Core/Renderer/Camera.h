#pragma once
#include "Core/CoreTypes.h"

class Camera
{
	float Aspect = 1.f;
	float Fov = 70.f;
	float Near = 0.1f;
	float Far = 500.f;

	glm::vec3 Front, Up;
	glm::mat4 ViewMatrix, ProjectionMatrix;
	static inline glm::mat4 ViewProjectionMatrix;
	static inline STransform CameraTransform;

	void CalculateViewMatrix();
	void CalculateProjectionMatrix();

public:
	Camera(const glm::vec3 Location, const float Fov);
	static const glm::mat4& GetViewProjection() { return ViewProjectionMatrix; };
	const glm::vec3& GetUp() { return Up; };
	const glm::vec3& GetFront() { return Front; };
	const glm::vec3 GetRight() { return glm::normalize(glm::cross(Front, Up)); };
	STransform GetCameraTransform() { return CameraTransform; };
	static glm::vec3 GetCameraLocation() { return CameraTransform.Location; };

	void AddCameraRotation(const glm::vec3 Rotation);
	void SetCameraRotation(const glm::vec3 Rotation);
	void SetCameraLocation(const glm::vec3 Location);
	void UpdateWindowSize(const int Width, const int Height);
	void SetFov(const float Fov);
};
