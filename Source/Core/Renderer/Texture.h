#pragma once
#include <string>
#include "Core/GL.h"

class Texture
{
	GLuint TextureID;
	GLsizei Width;
	GLsizei Height;

public:
	Texture(std::string FilePath);
	Texture() = delete;
	~Texture();

	GLuint GetTextureID() { return TextureID; };
	GLsizei GetTextureWidth() { return Width; };
	GLsizei GetTextureHeight() { return Height; };

	void Bind();
};
