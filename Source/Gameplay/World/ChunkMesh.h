#pragma once
#include "Core/CoreTypes.h"
#include "BlockTypes.h"
#include "Core/Renderer/Mesh.h"

class Chunks;

constexpr SPosition ChunkSize = { 16, 16, 16 };

enum class ECubeSides
{
	Top,
	Bottom,
	Front,
	Back,
	Left,
	Right
};

class ChunkMesh : public Mesh
{
	friend Chunks;

	Chunks* pChunksManager;
	SPosition2 ChunkPosition;
	std::array<std::array<std::array<SBlock, ChunkSize.X>, ChunkSize.Y>, ChunkSize.Z> BlocksData;

	void ChunkGeneration();
	const SPolygon4 CreateBlockSidePolygon(const SBlock* Block, const SPosition Position, const ECubeSides BlockSide);
	void GetBlockUV(const int TextureID, glm::vec2& Start, glm::vec2& End) const;

public:
	ChunkMesh(const SPosition2 InChunkLocation, Chunks* ChunksManager, MeshShader* Shader);
	bool PositionInChunkRange(const SPosition Position)
	{
		return Position >= SPosition{ 0, 0, 0 } && Position < ChunkSize;
	};

	SPosition BlockPositionToChunks(const SPosition BlockPosition) { return BlockPosition + SPosition{ ChunkPosition.X * ChunkSize.X, ChunkPosition.Y * ChunkSize.Y, 0 }; };
	
	[[nodiscard]] SBlock* GetBlock(const SPosition Position);
};
