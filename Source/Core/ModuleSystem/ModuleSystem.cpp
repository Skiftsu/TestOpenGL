#include "ModuleSystem.h"

#include "Gameplay/GameplayModule.h"
#include "Core/Renderer/Renderer.h"

ModuleSystem::ModuleSystem()
{
	Modules.push_back(new GameplayModule);
}

ModuleSystem::~ModuleSystem()
{
	for (auto i : Modules)
		delete i;
}

void ModuleSystem::Tick()
{
	const float DeltaTime = Renderer::GetDeltaTime();
	for (auto i : Modules)
		i->Tick(DeltaTime);
}
