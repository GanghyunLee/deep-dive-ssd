#pragma once
#include "ICommand.h"
#include "SsdEraseService.h"

class EraseRangeCommand : public ICommand
{
public:
	EraseRangeCommand(const std::shared_ptr<SsdEraseService>& ssdEraseService, int startLba, int endLba) :
		_ssdEraseService(ssdEraseService), _startLba(startLba), _endLba(endLba) {
	}
	~EraseRangeCommand() override = default;

	std::shared_ptr<IView> Execute() override;

	int GetStartLba() const { return _startLba; }
	int GetEndLba() const { return _endLba; }

protected:
	std::shared_ptr<SsdEraseService> _ssdEraseService;
	int _startLba = 0;
	int _endLba = 0;
};

