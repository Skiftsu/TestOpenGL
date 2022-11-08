#pragma once
#include <vector>
#include "BaseModule.h"


class ModuleSystem
{
	std::vector<BaseModule*> Modules;

public:
	ModuleSystem();
	~ModuleSystem();
	void Tick();
};
