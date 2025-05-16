#pragma once
#include <vector>

class ICommandMapper;

class IoC
{
public:
	std::vector<ICommandMapper*> GetCommandMappers();
};

