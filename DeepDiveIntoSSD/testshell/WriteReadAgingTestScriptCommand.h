#pragma once
#include "AbstractScriptCommand.h"
#include "WriteReadAgingTestScriptService.h"

class WriteReadAgingTestScriptCommand : public AbstractScriptCommand
{
public:
	WriteReadAgingTestScriptCommand(const std::shared_ptr<WriteReadAgingTestScriptService>& ssdScriptService) :
		AbstractScriptCommand(ssdScriptService) {
	}
	~WriteReadAgingTestScriptCommand() override = default;

protected:
	std::shared_ptr<IView> GetView() override;
};

