#pragma once
#include "ICommand.h"

class SsdReadService;
class ReadView;

class ReadCommand : public ICommand
{
public:
	ReadCommand(const std::shared_ptr<SsdReadService>& ssdReadService, int lba) :
		_ssdReadService(ssdReadService), _lba(lba) {
	}
	~ReadCommand() override = default;

	std::shared_ptr<IView> Execute() override;

	int GetLba() { return _lba; }

protected:
	std::shared_ptr<SsdReadService> _ssdReadService;
	int _lba = 0;
};

