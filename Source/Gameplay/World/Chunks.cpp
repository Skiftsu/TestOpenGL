#include "Chunks.h"
#include <iostream>

using namespace std;
using namespace glm;

Chunks::Chunks(MeshShader* ChunkShader)
	: pChunkShader(ChunkShader)
{
	pInstance = this;

	for (int X = 0; X < WorldSize.X; X++)
		for (int Y = 0; Y < WorldSize.Y; Y++)
			ChunksData.at(Y).at(X) = new ChunkMesh(SPosition2{ X, Y }, this, pChunkShader);
}

Chunks::~Chunks()
{
	for (auto i1 : ChunksData)
		for (auto i2 : i1)
			delete i2;
}

void Chunks::GenerateChunks()
{
	for (int X = 0; X < WorldSize.X; X++)
		for (int Y = 0; Y < WorldSize.Y; Y++)
			ChunksData.at(Y).at(X)->ChunkGeneration();
}

void Chunks::RenderChunks()
{
	for (auto i1 : ChunksData)
		for (auto i2 : i1)
			i2->DrawMesh();
}

ChunkMesh* Chunks::GetChunk(const SPosition2 Position) const
{
	if (Position.X < 0 || Position.Y < 0 || Position.X >= WorldSize.X || Position.Y >= WorldSize.Y)
		return nullptr;
	return ChunksData.at(Position.Y).at(Position.X);
}

SBlock* Chunks::GetBlock(const SPosition ChunksPosition)
{
	auto Chunk = GetChunk(ChunksPositionToChunk(ChunksPosition));
	if (!Chunk)
		return nullptr;
	return Chunk->GetBlock({ ChunksPosition.X % ChunkSize.X, ChunksPosition.Y % ChunkSize.Y, ChunksPosition.Z % ChunkSize.Z });
}

void Chunks::SetBlock(const SPosition ChunksPosition, const uint8_t Id)
{
	auto Block = GetBlock(ChunksPosition);
	if (!Block)
		return;
	Block->Id = Id;
	const SPosition2 CurrentChunk = ChunksPositionToChunk(ChunksPosition);

	ChunkMesh* Chunk = GetChunk(CurrentChunk);
	if (Chunk)
		Chunk->ChunkGeneration();
	Chunk = GetChunk(CurrentChunk + SPosition2{1, 0});
	if (Chunk)
		Chunk->ChunkGeneration();
	Chunk = GetChunk(CurrentChunk + SPosition2{ -1, 0 });
	if (Chunk)
		Chunk->ChunkGeneration();
	Chunk = GetChunk(CurrentChunk + SPosition2{ 0, 1 });
	if (Chunk)
		Chunk->ChunkGeneration();
	Chunk = GetChunk(CurrentChunk + SPosition2{ 0, -1 });
	if (Chunk)
		Chunk->ChunkGeneration();
}

bool Chunks::IsObstacle(const SPosition Position)
{
	auto Block = GetBlock(Position);
	if (!Block)
		return true; // void - is obstacle
	return Block->Id;
}

void Chunks::SetCenter(const SPosition Position)
{
	SPosition Pos = { Position.X / ChunkSize.X, Position.Y / ChunkSize.Y, Position.Z / ChunkSize.Z };
	Pos = Pos - ChunksCenter;
	if (Position.X < 0)
		Pos.X--;
	if (Position.Y < 0)
		Pos.Y--;
	if (Position.Z < 0)
		Pos.Z--;
	Pos = Pos - SPosition{ 4, 4, 0 };

	if (Pos.X != 0 || Pos.Y != 0 || Pos.Z != 0)
		Translate(Pos);
}

void Chunks::Translate(const SPosition Value)
{
}
