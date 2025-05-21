#pragma once
#include <functional>
#include "ICommand.h"
#include "SsdEraseService.h"

class EraseCommand;

class EraseCommand : public ICommand
{
public:
	EraseCommand(const std::shared_ptr<SsdEraseService>& ssdEraseService, int lba, int size) :
		_ssdEraseService(ssdEraseService), _lba(lba), _size(size) {
	}
	~EraseCommand() override = default;

	std::shared_ptr<IView> Execute() override;

	int GetLba() const { return _lba; }
	int GetSize() const { return _size; }

protected:
	std::shared_ptr<SsdEraseService> _ssdEraseService;
	int _lba = 0;
	int _size = 0;
};

