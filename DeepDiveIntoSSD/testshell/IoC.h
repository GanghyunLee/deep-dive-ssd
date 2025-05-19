#pragma once
#include <vector>
#include <memory>

#include "ICommand.h"
#include "SsdFullReadService.h"
#include "SsdFullWriteService.h"
#include "SsdReadService.h"
#include "SsdWriteService.h"

class ICommandMapper;

class IoC
{
public:
	std::vector<std::shared_ptr<ICommandMapper>> GetCommandMappers();
	std::shared_ptr<SsdWriteService> GetSsdWriteService();
	std::shared_ptr<SsdReadService> GetSsdReadService();
	std::shared_ptr<SsdFullWriteService> GetSsdFullWriteService();
	std::shared_ptr<SsdFullReadService> GetSsdFullReadService();
	
	
	std::shared_ptr<ISsdController> GetSsdController();
};

