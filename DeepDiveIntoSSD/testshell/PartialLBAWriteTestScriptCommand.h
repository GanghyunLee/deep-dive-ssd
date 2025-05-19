#pragma once
#include "ICommand.h"
#include "PartialLbaWriteTestScriptService.h"

class PartialLBAWriteTestScriptCommand : public ICommand
{
public:
	PartialLBAWriteTestScriptCommand(const std::shared_ptr<PartialLbaWriteTestScriptService>& ssdScriptService) :
		_ssdScriptService(ssdScriptService) {
	}
	~PartialLBAWriteTestScriptCommand() override = default;

	std::shared_ptr<IView> Execute() override;

protected:
	std::shared_ptr<PartialLbaWriteTestScriptService> _ssdScriptService;
};
