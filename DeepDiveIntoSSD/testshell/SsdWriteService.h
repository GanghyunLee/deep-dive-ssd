#pragma once
#include <memory>

#include "ISsdController.h"

class SsdWriteService
{
public:
	SsdWriteService( std::shared_ptr<ISsdController> ssdController) : _ssdController(ssdController)
	{
	}

	virtual ~SsdWriteService() = default;

public:
	virtual SsdWriteResult Write(int lba, unsigned int data);

protected:
	std::shared_ptr<ISsdController> _ssdController;
};

