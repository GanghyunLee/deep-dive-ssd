
#pragma once
#include "EraseAndWriteAgingTestScriptService.h"
#include "FullWriteAndReadCompareTestScriptService.h"
#include "ICommand.h"

class EraseAndWriteAgingTestScriptCommand : public ICommand
{
public:
	EraseAndWriteAgingTestScriptCommand(const std::shared_ptr<EraseAndWriteAgingTestScriptService>& ssdScriptService) :
		_ssdScriptService(ssdScriptService) {
	}
	~EraseAndWriteAgingTestScriptCommand() override = default;

	std::shared_ptr<IView> Execute() override;

protected:
	std::shared_ptr<EraseAndWriteAgingTestScriptService> _ssdScriptService;
};

