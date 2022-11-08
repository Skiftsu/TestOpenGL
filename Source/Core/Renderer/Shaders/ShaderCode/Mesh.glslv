#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 a_texCoord;
layout (location = 2) in vec3 a_normal;

out vec2 texCoord;
out vec3 pos;
out vec3 normal;

uniform mat4 worldlocation;
uniform mat4 projeview;

void main()
{
	vec4 OGLCoordinateSystem = worldlocation * vec4(position.x, position.y, position.z, 1.f);
	pos = vec3(OGLCoordinateSystem.x, OGLCoordinateSystem.z, -OGLCoordinateSystem.y);
	texCoord = a_texCoord;
	gl_Position = projeview * vec4(pos, 1.f);

	normal = mat3(transpose(inverse(worldlocation))) * a_normal;
}