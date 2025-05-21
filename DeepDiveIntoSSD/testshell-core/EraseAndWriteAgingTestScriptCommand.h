
#pragma once
#include "AbstractScriptCommand.h"
#include "EraseAndWriteAgingTestScriptService.h"
#include "FullWriteAndReadCompareTestScriptService.h"

class EraseAndWriteAgingTestScriptCommand : public AbstractScriptCommand
{
public:
	EraseAndWriteAgingTestScriptCommand(const std::shared_ptr<EraseAndWriteAgingTestScriptService>& ssdScriptService) :
		AbstractScriptCommand(ssdScriptService) {
	}
	~EraseAndWriteAgingTestScriptCommand() override = default;

	std::shared_ptr<IView> GetView() override;
	std::string GetCommandName() override { return "4_EraseAndWriteAging"; }
};

