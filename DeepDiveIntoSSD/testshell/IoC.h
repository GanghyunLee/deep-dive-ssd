#pragma once
#include <vector>
#include <memory>

#include "EraseAndWriteAgingTestScriptService.h"
#include "EraseCommand.h"
#include "FullWriteAndReadCompareTestScriptService.h"
#include "ICommand.h"
#include "PartialLbaWriteTestScriptService.h"
#include "SsdFullReadService.h"
#include "SsdFullWriteService.h"
#include "SsdReadService.h"
#include "SsdWriteService.h"
#include "WriteReadAgingTestScriptService.h"

class ICommandMapper;

class IoC
{
public:
	std::vector<std::shared_ptr<ICommandMapper>> GetCommandMappers();
	std::shared_ptr<SsdWriteService> GetSsdWriteService();
	std::shared_ptr<SsdReadService> GetSsdReadService();
	std::shared_ptr<SsdFullWriteService> GetSsdFullWriteService();
	std::shared_ptr<SsdFullReadService> GetSsdFullReadService();
	std::shared_ptr<SsdEraseService> GetSsdEraseService();
	std::shared_ptr<FullWriteAndReadCompareTestScriptService> GetFullWriteAndReadCompareTestScriptService();
	std::shared_ptr<PartialLbaWriteTestScriptService> GetPartialLbaWriteTestScriptService();
	std::shared_ptr<WriteReadAgingTestScriptService> GetWriteReadAgingTestScriptService();
	std::shared_ptr<EraseAndWriteAgingTestScriptService> GetEraseAndWriteAgingTestScriptService();
	std::shared_ptr<ISsdController> GetSsdController();

protected:
	EraseCommandFactory GenerateEraseCommandFactory();
};

