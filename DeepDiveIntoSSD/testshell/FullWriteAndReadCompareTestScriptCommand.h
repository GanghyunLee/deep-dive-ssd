#pragma once
#include "FullWriteAndReadCompareTestScriptService.h"
#include "ICommand.h"

class FullWriteAndReadCompareTestScriptCommand : public ICommand
{
public:
	FullWriteAndReadCompareTestScriptCommand(const std::shared_ptr<FullWriteAndReadCompareTestScriptService>& ssdScriptService) :
		_ssdScriptService(ssdScriptService) {
	}
	~FullWriteAndReadCompareTestScriptCommand() override = default;

	std::shared_ptr<IView> Execute() override;

protected:
	std::shared_ptr<FullWriteAndReadCompareTestScriptService> _ssdScriptService;
};

