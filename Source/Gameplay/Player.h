#pragma once
#include "Core/CoreTypes.h"
#include "World/BlockTypes.h"
#include <vector>

class Camera;
class BaseShader;

class Player
{
	Camera* pCamera;
	STransform Transform;

	glm::vec2 MovementDirection = glm::vec2(0);

	float DeltaSeconds = 0.f;

	bool RayCast(glm::vec3 Start, glm::vec3 Direction, SPosition& BlockPosition, SPosition& Face);
	float MaxPlayerSpeed = 4.f;
	float PlayerSpeed;

public:
	void Tick(const float DeltaSeconds);
	Player();
	~Player();

	void MovementInput();
};
