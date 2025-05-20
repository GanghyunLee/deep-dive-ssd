#pragma once
#include "ICommand.h"
#include "SsdFlushService.h"

class FlushCommand : public ICommand
{
public:
	FlushCommand(const std::shared_ptr<SsdFlushService>& ssdFlushService) : _ssdFlushService(ssdFlushService) { }
	~FlushCommand() override = default;

public:
	std::shared_ptr<IView> Execute() override;

protected:
	std::shared_ptr<SsdFlushService> _ssdFlushService;
};

