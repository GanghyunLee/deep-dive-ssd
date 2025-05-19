#pragma once
#include "ICommand.h"

class SsdWriteService;
class WriteView;

class WriteCommand : public ICommand
{
public:
	WriteCommand(const std::shared_ptr<SsdWriteService>& ssdWriteService) : _ssdWriteService(ssdWriteService) { }
	~WriteCommand() override = default;

	std::shared_ptr<IView> Execute() override;

public:
	void SetLBA(int LBA) { _lba = LBA; }
	int GetLBA() const { return _lba; }

	void SetData(unsigned int data) { _data = data; }
	unsigned int GetData() const { return _data; }

protected:
	std::shared_ptr<SsdWriteService> _ssdWriteService;
	int _lba = 0;
	unsigned int _data = 0;
};

