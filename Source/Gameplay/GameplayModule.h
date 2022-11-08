#pragma once
#include "Core/ModuleSystem/BaseModule.h"

class Player;
class World;
class GameUI;

class GameplayModule : public BaseModule
{
	Player* pPlayer;
	World* pWorld;
	GameUI* pGameUI;

public:
	GameplayModule();
	~GameplayModule();
	virtual void Tick(const float DeltaTime) override;
};
