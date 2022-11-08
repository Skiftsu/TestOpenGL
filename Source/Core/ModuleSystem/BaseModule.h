#pragma once

class BaseModule
{
public:
	virtual void Tick(const float DeltaSeconds) = 0;
};