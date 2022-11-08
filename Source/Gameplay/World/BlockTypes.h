#pragma once
#include <array>

struct SBlock
{
	uint8_t Id = 0; // 0 - Air(None)
	const bool IsBlock() const { return Id > 0; };
};

struct SBlockData
{
	uint8_t Id = 0; // 0 - Air(None)
	uint8_t TopTextureID = 0;
	uint8_t LRFBTextureID = 0;
	uint8_t BottomTextureID = 0;
};