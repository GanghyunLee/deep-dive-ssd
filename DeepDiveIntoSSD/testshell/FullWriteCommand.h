#pragma once
#include "ICommand.h"
#include "SsdFullWriteService.h"

class SsdWriteService;
class WriteView;

class FullWriteCommand : public ICommand
{
public:
	FullWriteCommand(const std::shared_ptr<SsdFullWriteService>& ssdFullWriteService, unsigned int data) :
		_ssdFullWriteService(ssdFullWriteService), _data(data) {
	}
	~FullWriteCommand() override = default;

	std::shared_ptr<IView> Execute() override;

	unsigned int GetData() { return _data; }

protected:
	std::shared_ptr<SsdFullWriteService> _ssdFullWriteService;
	unsigned int _data = 0;
};

