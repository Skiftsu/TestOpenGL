#include "World.h"
#include "Chunks.h"
#include "Core/Renderer/Shaders/MeshShader.h"

World::World()
{
	pChunkShader = new MeshShader("Resources/atlas.png");
	pWorld = this;
	pChunks = new Chunks(pChunkShader);
	
	pChunks->GenerateChunks();
}

World::~World()
{
	delete pChunks;
	delete pChunkShader;
}

void World::Tick(const float DeltaTime)
{
	pChunks->RenderChunks();
}
