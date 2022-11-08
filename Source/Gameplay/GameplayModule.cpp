#include "GameplayModule.h"
#include "Player.h"
#include "World/World.h"
#include "Gameplay/UI/GameUI.h"

GameplayModule::GameplayModule()
{
	pWorld = new World();
	pPlayer = new Player();
	pGameUI = new GameUI();
}

GameplayModule::~GameplayModule()
{
	delete pPlayer;
	delete pWorld;
	delete pGameUI;
}

void GameplayModule::Tick(const float DeltaTime)
{
	if (pPlayer)
		pPlayer->Tick(DeltaTime);
	
	if (pWorld)
		pWorld->Tick(DeltaTime);

	if (pGameUI)
		pGameUI->Tick(DeltaTime);
}
