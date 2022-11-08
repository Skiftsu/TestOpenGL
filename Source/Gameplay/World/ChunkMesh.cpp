#include "ChunkMesh.h"
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <gtc/noise.hpp>
#include <gtx/rotate_vector.hpp>

#include "Chunks.h"
#include "Gameplay/BlocksData.h"
#include "Core/Utils.h"

using namespace std;
using namespace glm;

ChunkMesh::ChunkMesh(const SPosition2 InChunkPosition, Chunks* ChunksManager, MeshShader* Shader)
	: Mesh(Shader), ChunkPosition(InChunkPosition), pChunksManager(ChunksManager)
{
	Transform = translate(Transform, vec3(ChunkPosition.X * ChunkSize.X + 0.5f, ChunkPosition.Y * ChunkSize.Y + 0.5f, 0.5f));

	for (int X = 0; X < ChunkSize.X; X++)
		for (int Y = 0; Y < ChunkSize.Y; Y++)
			for (int Z = 0; Z < ChunkSize.Z; Z++)
			{
				SPosition BlocksPosition = BlockPositionToChunks({ X, Y, Z });
				int ID = perlin(vec3(BlocksPosition.X * 0.0225f, BlocksPosition.Z * 0.0225f, -BlocksPosition.Y * 0.0225f)) > 0.1f;
				auto BlockWorldPos = BlockPositionToChunks({ X, Y, Z });
				if (BlocksPosition.Z <= 2)
					ID = 2;
				GetBlock({ X, Y, Z })->Id = ID; // ID
			}
}

SBlock* ChunkMesh::GetBlock(const SPosition Position)
{
	if (!PositionInChunkRange(Position))
		return nullptr;

	return &BlocksData.at(Position.Z).at(Position.Y).at(Position.X);
}

void ChunkMesh::ChunkGeneration()
{
	vector<SPolygon4> BufferPolygons;
	for (int X = 0; X < ChunkSize.X; X++)
		for (int Y = 0; Y < ChunkSize.Y; Y++)
			for (int Z = 0; Z < ChunkSize.Z; Z++)
			{
				SPosition CurrentPosition = { X, Y, Z };
				auto CurrentBlock = GetBlock(CurrentPosition);
				if (!CurrentBlock->IsBlock())
					continue;

				// Cube side on a chunk border
				if (Y == 0 || Y == ChunkSize.Y - 1 || X == 0 || X == ChunkSize.X - 1)
				{
					ChunkMesh* AnotherChunk;
					if (Y == 0)
					{
						AnotherChunk = pChunksManager->GetChunk({ ChunkPosition.X, ChunkPosition.Y - 1 });
						if (!AnotherChunk || !AnotherChunk->GetBlock({ X, ChunkSize.Y - 1, Z })->IsBlock())
							BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Front));
					}
					else if (Y == ChunkSize.Y - 1)
					{
						AnotherChunk = pChunksManager->GetChunk({ ChunkPosition.X, ChunkPosition.Y + 1 });
						if (!AnotherChunk || !AnotherChunk->GetBlock({ X, 0, Z })->IsBlock())
							BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Back));
					}
					if (X == 0)
					{
						AnotherChunk = pChunksManager->GetChunk({ ChunkPosition.X - 1, ChunkPosition.Y });
						if (!AnotherChunk || !AnotherChunk->GetBlock({ ChunkSize.X - 1, Y, Z })->IsBlock())
							BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Left));
					}
					else if (X == ChunkSize.X - 1)
					{
						AnotherChunk = pChunksManager->GetChunk({ ChunkPosition.X + 1, ChunkPosition.Y });
						if (!AnotherChunk || !AnotherChunk->GetBlock({ 0, Y, Z })->IsBlock())
							BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Right));
					}
				}

				if (!PositionInChunkRange({ X, Y, Z + 1 }) || !GetBlock({ X, Y, Z + 1 })->IsBlock())
					BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Top));
				if (!PositionInChunkRange({ X, Y, Z - 1 }) || !GetBlock({ X, Y, Z - 1 })->IsBlock())
					BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Bottom));
				if (PositionInChunkRange({ X, Y - 1, Z }) && !GetBlock({ X, Y - 1, Z })->IsBlock())
					BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Front));
				if (PositionInChunkRange({ X, Y + 1, Z }) && !GetBlock({ X, Y + 1, Z })->IsBlock())
					BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Back));
				if (PositionInChunkRange({ X - 1, Y, Z }) && !GetBlock({ X - 1, Y, Z })->IsBlock())
					BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Left));
				if (PositionInChunkRange({ X + 1, Y, Z }) && !GetBlock({ X + 1, Y, Z })->IsBlock())
					BufferPolygons.push_back(CreateBlockSidePolygon(CurrentBlock, CurrentPosition, ECubeSides::Right));
			}

	SetPolygons4(BufferPolygons);
}

const SPolygon4 ChunkMesh::CreateBlockSidePolygon(const SBlock* Block, const SPosition Position, const ECubeSides BlockSide)
{
	constexpr float SideSize = 0.5f;

	vec2 Start(0), End(1);
	const auto BlockData = GetBlockData(Block->Id);
	GetBlockUV(BlockSide == ECubeSides::Top	  ? BlockData.TopTextureID	  //
			: BlockSide == ECubeSides::Bottom ? BlockData.BottomTextureID //
											  : BlockData.LRFBTextureID,
		Start, End); //
	SPolygon4 SidePolygon = {
		{ { -SideSize, 0, SideSize }, Start },				 // Top Left
		{ { -SideSize, 0, -SideSize }, { Start.x, End.y } }, // Bottom Left
		{ { SideSize, 0, -SideSize }, End },				 // Bottom Right
		{ { SideSize, 0, SideSize }, { End.x, Start.y } }	 // Top Rgiht
	};
	vec3 Normals;
	switch (BlockSide)
	{
		case ECubeSides::Front:
			SidePolygon.Vertex1.Position -= vec3(0, SideSize, 0);
			SidePolygon.Vertex2.Position -= vec3(0, SideSize, 0);
			SidePolygon.Vertex3.Position -= vec3(0, SideSize, 0);
			SidePolygon.Vertex4.Position -= vec3(0, SideSize, 0);

			Normals = { 0, 0, 1 };
			SidePolygon.Vertex1.Normals = SidePolygon.Vertex2.Normals = SidePolygon.Vertex3.Normals = SidePolygon.Vertex4.Normals = Normals;
			break;
		case ECubeSides::Back:
			SidePolygon.Vertex1.Position = rotateZ(SidePolygon.Vertex1.Position, radians(180.f)) + vec3(0, SideSize, 0);
			SidePolygon.Vertex2.Position = rotateZ(SidePolygon.Vertex2.Position, radians(180.f)) + vec3(0, SideSize, 0);
			SidePolygon.Vertex3.Position = rotateZ(SidePolygon.Vertex3.Position, radians(180.f)) + vec3(0, SideSize, 0);
			SidePolygon.Vertex4.Position = rotateZ(SidePolygon.Vertex4.Position, radians(180.f)) + vec3(0, SideSize, 0);

			Normals = { 0, 0, -1 };
			SidePolygon.Vertex1.Normals = SidePolygon.Vertex2.Normals = SidePolygon.Vertex3.Normals = SidePolygon.Vertex4.Normals = Normals;
			break;
		case ECubeSides::Top:
			SidePolygon.Vertex1.Position = rotateX(SidePolygon.Vertex1.Position, radians(-90.f)) + vec3(0, 0, SideSize);
			SidePolygon.Vertex2.Position = rotateX(SidePolygon.Vertex2.Position, radians(-90.f)) + vec3(0, 0, SideSize);
			SidePolygon.Vertex3.Position = rotateX(SidePolygon.Vertex3.Position, radians(-90.f)) + vec3(0, 0, SideSize);
			SidePolygon.Vertex4.Position = rotateX(SidePolygon.Vertex4.Position, radians(-90.f)) + vec3(0, 0, SideSize);

			Normals = { 0, 1, 0 };
			SidePolygon.Vertex1.Normals = SidePolygon.Vertex2.Normals = SidePolygon.Vertex3.Normals = SidePolygon.Vertex4.Normals = Normals;
			break;
		case ECubeSides::Bottom:
			SidePolygon.Vertex1.Position = rotateX(SidePolygon.Vertex1.Position, radians(90.f)) - vec3(0, 0, SideSize);
			SidePolygon.Vertex2.Position = rotateX(SidePolygon.Vertex2.Position, radians(90.f)) - vec3(0, 0, SideSize);
			SidePolygon.Vertex3.Position = rotateX(SidePolygon.Vertex3.Position, radians(90.f)) - vec3(0, 0, SideSize);
			SidePolygon.Vertex4.Position = rotateX(SidePolygon.Vertex4.Position, radians(90.f)) - vec3(0, 0, SideSize);

			Normals = { 0, -1, 0 };
			SidePolygon.Vertex1.Normals = SidePolygon.Vertex2.Normals = SidePolygon.Vertex3.Normals = SidePolygon.Vertex4.Normals = Normals;
			break;
		case ECubeSides::Left:
			SidePolygon.Vertex1.Position = rotateZ(SidePolygon.Vertex1.Position, radians(-90.f)) - vec3(SideSize, 0, 0);
			SidePolygon.Vertex2.Position = rotateZ(SidePolygon.Vertex2.Position, radians(-90.f)) - vec3(SideSize, 0, 0);
			SidePolygon.Vertex3.Position = rotateZ(SidePolygon.Vertex3.Position, radians(-90.f)) - vec3(SideSize, 0, 0);
			SidePolygon.Vertex4.Position = rotateZ(SidePolygon.Vertex4.Position, radians(-90.f)) - vec3(SideSize, 0, 0);

			Normals = { -1, 0, 0 };
			SidePolygon.Vertex1.Normals = SidePolygon.Vertex2.Normals = SidePolygon.Vertex3.Normals = SidePolygon.Vertex4.Normals = Normals;
			break;
		case ECubeSides::Right:
			SidePolygon.Vertex1.Position = rotateZ(SidePolygon.Vertex1.Position, radians(90.f)) + vec3(SideSize, 0, 0);
			SidePolygon.Vertex2.Position = rotateZ(SidePolygon.Vertex2.Position, radians(90.f)) + vec3(SideSize, 0, 0);
			SidePolygon.Vertex3.Position = rotateZ(SidePolygon.Vertex3.Position, radians(90.f)) + vec3(SideSize, 0, 0);
			SidePolygon.Vertex4.Position = rotateZ(SidePolygon.Vertex4.Position, radians(90.f)) + vec3(SideSize, 0, 0);

			Normals = { 1, 0, 0 };
			SidePolygon.Vertex1.Normals = SidePolygon.Vertex2.Normals = SidePolygon.Vertex3.Normals = SidePolygon.Vertex4.Normals = Normals;
			break;
	}

	return SidePolygon + Position;
}

void ChunkMesh::GetBlockUV(const int TextureID, vec2& Start, vec2& End) const
{
	constexpr float texture_atlas_size = 512.f;
	constexpr float texture_size = 32.f;
	constexpr int texture_elements = texture_atlas_size / texture_size;
	constexpr float uvsize = 1.f / texture_elements;
	if (TextureID >= texture_elements * texture_elements)
	{
		Start = { 0, 0 };
		End = { uvsize, uvsize };
		return;
	}

	int posY = TextureID / texture_elements;
	int posX = TextureID - int(posY * texture_elements) % texture_elements;

	ivec2 TexturePos(posX, posY);
	Start = vec2(TexturePos.x * uvsize, TexturePos.y * uvsize);
	End = vec2((TexturePos.x + 1.f) * uvsize, (TexturePos.y + 1.f) * uvsize);
}