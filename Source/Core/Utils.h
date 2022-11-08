#pragma once
#include <iostream>
#include <glm.hpp>

static glm::vec3 ConvertCoordinateSystem(glm::vec3 Vector)
{
	return { Vector.x, -Vector.z, Vector.y };
}