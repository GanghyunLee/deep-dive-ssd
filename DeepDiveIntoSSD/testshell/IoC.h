#pragma once
#include <vector>
#include <memory>

#include "ICommand.h"
#include "SsdWriteService.h"

class ICommandMapper;

class IoC
{
public:
	std::vector<std::shared_ptr<ICommandMapper>> GetCommandMappers();
	std::shared_ptr<SsdWriteService> GetSsdWriteService();
	std::shared_ptr<ISsdController> GetSsdController();
};

