#pragma once
#include "ICommand.h"
#include "SsdFullReadService.h"

class FullReadCommand : public ICommand
{
public:
	FullReadCommand(const std::shared_ptr<SsdFullReadService>& ssdFullReadService) :
		_ssdFullReadService(ssdFullReadService) {
	}
	~FullReadCommand() override = default;

	std::shared_ptr<IView> Execute() override;

protected:
	std::shared_ptr<SsdFullReadService> _ssdFullReadService;
};
