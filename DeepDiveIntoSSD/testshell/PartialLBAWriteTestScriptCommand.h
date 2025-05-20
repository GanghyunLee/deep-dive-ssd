#pragma once
#include "AbstractScriptCommand.h"
#include "ICommand.h"
#include "PartialLbaWriteTestScriptService.h"

class PartialLBAWriteTestScriptCommand : public AbstractScriptCommand
{
public:
	PartialLBAWriteTestScriptCommand(const std::shared_ptr<PartialLbaWriteTestScriptService>& ssdScriptService) :
		AbstractScriptCommand(ssdScriptService) {
	}
	~PartialLBAWriteTestScriptCommand() override = default;

	std::shared_ptr<IView> GetView() override;
	std::string GetCommandName() override { return "2_PartialLBAWrite"; }
};


