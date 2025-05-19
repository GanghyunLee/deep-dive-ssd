#pragma once
#include "ICommand.h"

class SsdWriteService;
class WriteView;

class WriteCommand : public ICommand
{
public:
	WriteCommand(const std::shared_ptr<SsdWriteService>& ssdWriteService, int lba, unsigned int data) :
		_ssdWriteService(ssdWriteService), _lba(lba), _data(data) { }
	~WriteCommand() override = default;

	std::shared_ptr<IView> Execute() override;

protected:
	std::shared_ptr<SsdWriteService> _ssdWriteService;
	int _lba = 0;
	unsigned int _data = 0;
};

