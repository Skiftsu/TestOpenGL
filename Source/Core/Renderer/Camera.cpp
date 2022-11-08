#include "Camera.h"
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include "Core/Application.h"

using namespace glm;


Camera::Camera(const glm::vec3 Location, const float Fov)
	: Fov(Fov), Aspect(Aspect)
{
	CameraTransform.Location = Location;
	Front = vec3(0.f, 0.f, 1.f);
	Up = vec3(0.f, 1.f, 0.f);
	int Width, Height;
	Application::GetInstance()->GetWindowSize(Width, Height);
	UpdateWindowSize(Width, Height);

	SetCameraRotation(vec3(270.f, 0.f, 0.f));

	Application::GetInstance()->onUpdateWindowSize.append([this](int Width, int Height) { UpdateWindowSize(Width, Height); });
}

void Camera::CalculateViewMatrix()
{
	ViewMatrix = lookAt(CameraTransform.Location, CameraTransform.Location + Front, Up);

	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}

void Camera::CalculateProjectionMatrix()
{
	ProjectionMatrix = perspective(Fov, Aspect, Near, Far);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}

void Camera::AddCameraRotation(const vec3 Rotation)
{
	SetCameraRotation(CameraTransform.Rotation + Rotation);
}

void Camera::SetCameraRotation(const vec3 Rotation)
{
	CameraTransform.Rotation = Rotation;
	CameraTransform.Rotation.y = clamp(CameraTransform.Rotation.y, -89.f, 89.f);
	Front.x = cos(radians(CameraTransform.Rotation.x)) * cos(radians(CameraTransform.Rotation.y));
	Front.y = sin(radians(CameraTransform.Rotation.y));
	Front.z = sin(radians(CameraTransform.Rotation.x)) * cos(radians(CameraTransform.Rotation.y));
	normalize(Front);

	CalculateViewMatrix();
}

void Camera::SetCameraLocation(const vec3 Location)
{
	CameraTransform.Location = Location;
	CalculateViewMatrix();
}

void Camera::UpdateWindowSize(const int Width, const int Height)
{
	Aspect = static_cast<float>(Width)/static_cast<float>(Height);
	CalculateProjectionMatrix();
}

void Camera::SetFov(const float InFov)
{
	Fov = InFov;
	CalculateProjectionMatrix();
}
