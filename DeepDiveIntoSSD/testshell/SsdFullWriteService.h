#pragma once
#include <memory>
#include <vector>

#include "ISsdController.h"

class SsdFullWriteService
{
	enum
	{
		MAX_LBA = 99
	};

public:
	SsdFullWriteService(std::shared_ptr<ISsdController> ssdController) : _ssdController(ssdController)
	{
	}

	virtual ~SsdFullWriteService() = default;

public:
	virtual std::vector<SsdWriteResult> FullWrite(unsigned int data);

protected:
	std::shared_ptr<ISsdController> _ssdController;
};

