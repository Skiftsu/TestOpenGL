#include "Player.h"
#include <iostream>
#include "Core/Utils.h"
#include <callbacklist.h>
#include <gtc/matrix_transform.hpp>
#include "Core/Events/EventSystem.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Camera.h"
#include "Core/Application.h"
#include "World/World.h"
#include "World/Chunks.h"

using namespace std;
using namespace glm;

Player::Player()
{
	pCamera = Renderer::GetCamera();
	pCamera->SetCameraLocation({ 0, 10, 10 });
	EventSystem::GetEventSystem()->onKeyButtonDown.append([&](const EKey Key, const EKeyState Action) {
		float Value = 25.f;
		if (Key == EKey::Escape)
			Application::GetInstance()->CloseWindow();
		else if (Key == EKey::W && Action != EKeyState::Repeat)
			MovementDirection.y = Action == EKeyState::Press ? Value : 0;
		else if (Key == EKey::S && Action != EKeyState::Repeat)
			MovementDirection.y = Action == EKeyState::Press ? -Value : 0;
		else if (Key == EKey::A && Action != EKeyState::Repeat)
			MovementDirection.x = Action == EKeyState::Press ? -Value : 0;
		else if (Key == EKey::D && Action != EKeyState::Repeat)
			MovementDirection.x = Action == EKeyState::Press ? Value : 0;
	});

	EventSystem::GetEventSystem()->onCursorMoved.append([&](const double PosX, const double PosY) {
		vec2 MoousePosition = vec2(PosX, PosY);
		static vec2 OldMousePosition;

		static bool First = true;
		if (First)
		{
			OldMousePosition = MoousePosition;
			First = false;
		}

		vec2 MouseOffset = MoousePosition - OldMousePosition;
		constexpr GLfloat Sensitivity = 5.f;
		MouseOffset *= DeltaSeconds * Sensitivity;
		MouseOffset.y *= -1.f;
		pCamera->AddCameraRotation(vec3(MouseOffset, 0.f));

		OldMousePosition = MoousePosition;
	});
	EventSystem::GetEventSystem()->onMouseButtonDown.append([&](const EMouseButton Button, const EKeyState Action) {
		if (Button == EMouseButton::Left && Action == EKeyState::Press)
		{
			SPosition BlockPosition;
			SPosition Face;
			if (RayCast(ConvertCoordinateSystem(pCamera->GetCameraLocation()), ConvertCoordinateSystem(pCamera->GetFront() * 50.f + pCamera->GetCameraLocation()), BlockPosition, Face))
				World::GetWorld()->GetChunks()->SetBlock(BlockPosition, 0);
		}
		else if (Button == EMouseButton::Right && Action == EKeyState::Press)
		{
			SPosition BlockPosition;
			SPosition Face;
			if (RayCast(ConvertCoordinateSystem(pCamera->GetCameraLocation()), ConvertCoordinateSystem(pCamera->GetFront() * 50.f + pCamera->GetCameraLocation()), BlockPosition, Face))
				World::GetWorld()->GetChunks()->SetBlock(Face, 1);
		}
	});
}

Player::~Player()
{
}

void Player::MovementInput()
{
	vec3 MovementDirectionVector = pCamera->GetFront() * MovementDirection.y + pCamera->GetRight() * MovementDirection.x;
	vec3 NewLoc = pCamera->GetCameraLocation() + MovementDirectionVector * DeltaSeconds;
	pCamera->SetCameraLocation(NewLoc);
}

bool Player::RayCast(vec3 Start, vec3 End, SPosition& BlockPosition, SPosition& Face)
{
	float Lenght = length(End - Start);
	const vec3 RayVector = normalize(End - Start) / Lenght;
	const auto Chunks = World::GetChunks();
	const ivec3 EndBlock(End);

	vec3 RayPosition(Start);
	ivec3 CurrentBlock(Start);
	ivec3 OldBlock(Start);

	while (EndBlock != CurrentBlock) 
	{
		RayPosition += RayVector;
		CurrentBlock = floor(RayPosition);
		if (CurrentBlock == OldBlock)
			continue;
		SPosition Position = { CurrentBlock.x, CurrentBlock.y, CurrentBlock.z };

		auto Block = Chunks->GetBlock(Position);
		if (Block && Block->IsBlock()) 
		{
			BlockPosition = Position;
			Face = { OldBlock.x, OldBlock.y, OldBlock.z };
			return true;
		}
		OldBlock = CurrentBlock;
	}
	return false;
}

void Player::Tick(const float InDeltaSeconds)
{
	DeltaSeconds = InDeltaSeconds;
	MovementInput();
}
