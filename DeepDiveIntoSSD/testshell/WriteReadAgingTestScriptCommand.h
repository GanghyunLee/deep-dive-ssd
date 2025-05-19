#pragma once
#include "ICommand.h"
#include "WriteReadAgingTestScriptService.h"

class WriteReadAgingTestScriptCommand : public ICommand
{
public:
	WriteReadAgingTestScriptCommand(const std::shared_ptr<WriteReadAgingTestScriptService>& ssdScriptService) :
		_ssdScriptService(ssdScriptService) {
	}
	~WriteReadAgingTestScriptCommand() override = default;

	std::shared_ptr<IView> Execute() override;

protected:
	std::shared_ptr<WriteReadAgingTestScriptService> _ssdScriptService;
};

