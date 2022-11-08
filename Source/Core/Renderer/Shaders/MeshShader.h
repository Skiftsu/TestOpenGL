#pragma once
#include "BaseShader.h"
#include <string>

class Mesh;
class Texture;

class MeshShader : public BaseShader
{
	Texture* pTexture;

public:
	MeshShader(std::string TextureFilePath);
	MeshShader() = delete;
	~MeshShader();
	void Use(Mesh* IMesh);
};
