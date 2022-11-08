#include "MeshShader.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/Camera.h"
#include "Core/Renderer/Texture.h"

#define VertexShaderFilePatch "Source/Core/Renderer/Shaders/ShaderCode/Mesh.glslv"
#define FragmnetShaderFilePatch "Source/Core/Renderer/Shaders/ShaderCode/Mesh.glslf"

using namespace std;

MeshShader::MeshShader(string TextureFilePath)
	: BaseShader(VertexShaderFilePatch, FragmnetShaderFilePatch)
{
	pTexture = new Texture(TextureFilePath);
}

MeshShader::~MeshShader()
{
	delete pTexture;
}

void MeshShader::Use(Mesh* IMesh)
{
	BaseShader::Use();
	UniformMatrix("worldlocation", IMesh->Transform);
	UniformMatrix("projeview", Camera::GetViewProjection());
	UniformVec3("viewPos", Camera::GetCameraLocation());
	UniformVec3("lightPos", {1.f, 1.f, 1.f});
	UniformVec3("lightColor", { 1.f, 1.f, 1.f });
	pTexture->Bind();
}
