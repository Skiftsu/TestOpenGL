#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

using namespace std;

Texture::Texture(string FilePath)
{
	int Cnt;
	unsigned char* ImageData = stbi_load(FilePath.c_str(), &Width, &Height, &Cnt, 0);

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID); // Start

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, Cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, ImageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0); // End

	stbi_image_free(ImageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &TextureID);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, TextureID);
}
