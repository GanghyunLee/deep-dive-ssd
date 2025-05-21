#pragma once
#include "AbstractScriptCommand.h"
#include "FullWriteAndReadCompareTestScriptService.h"

class FullWriteAndReadCompareTestScriptCommand : public AbstractScriptCommand
{
public:
	FullWriteAndReadCompareTestScriptCommand(const std::shared_ptr<FullWriteAndReadCompareTestScriptService>& ssdScriptService) :
		AbstractScriptCommand(ssdScriptService) {
	}
	~FullWriteAndReadCompareTestScriptCommand() override = default;

	std::shared_ptr<IView> GetView() override;
	std::string GetCommandName() override { return "1_FullWriteAndReadCompare"; }
};

