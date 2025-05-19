#pragma once
#include <vector>
#include <memory>

class ICommandMapper;

class IoC
{
public:
	std::vector<std::shared_ptr<ICommandMapper>> GetCommandMappers();
};

