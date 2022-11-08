#pragma once
#include "World/BlockTypes.h"
#include <array>

// 	ID, TopTextureID, LRFBTextureID, BottomTextureID
constexpr std::array<SBlockData, 2> BlocksArray{ { 
	{ 1, 2, 1, 3 }, // Test block
	{ 2, 16, 17, 16 } 
} };

inline const SBlockData GetBlockData(const int BlockID)
{
	if (BlockID > BlocksArray.size())
		return SBlockData();
	return BlocksArray.at(BlockID - 1);
}