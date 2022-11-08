#pragma once

class Chunks;
class MeshShader;

class World
{
	static inline Chunks* pChunks;
	static inline World* pWorld;
	MeshShader* pChunkShader;

public:
	World();
	~World();
	void Tick(const float DeltaTime);
	static Chunks* GetChunks() { return pChunks; };
	static World* GetWorld() { return pWorld; };
};
