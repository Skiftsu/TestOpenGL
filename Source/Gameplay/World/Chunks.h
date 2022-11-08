#pragma once
#include "ChunkMesh.h"

class ChunkMesh;
class MeshShader;

constexpr SPosition2 WorldSize = { 8, 8 };

class Chunks
{
	static inline Chunks* pInstance;
	std::array<std::array<ChunkMesh*, WorldSize.X>, WorldSize.Y> ChunksData;
	MeshShader* pChunkShader;

public:
	static Chunks* GetInstance() { return pInstance; };

	Chunks(MeshShader* ChunkShader);
	~Chunks();
	
	void GenerateChunks();
	void RenderChunks();
	[[nodiscard]] SPosition2 ChunksPositionToChunk(const SPosition ChunksPosition) const { return { ChunksPosition.X / ChunkSize.X, ChunksPosition.Y / ChunkSize.Y }; }
	[[nodiscard]] ChunkMesh* GetChunk(const SPosition2 Position) const;
	[[nodiscard]] SBlock* GetBlock(const SPosition ChunksPosition);
	void SetBlock(const SPosition ChunksPosition, const uint8_t Id);

	bool IsObstacle(const SPosition Position);

	SPosition ChunksCenter;
	void SetCenter(const SPosition Position);
	void Translate(const SPosition Value);
};
