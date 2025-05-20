#pragma once
#include <memory>
#include "ISsdController.h"

class SsdFlushService
{
public:
	SsdFlushService(std::shared_ptr<ISsdController> ssdController) : _ssdController(ssdController)
	{
	}

	virtual ~SsdFlushService() = default;

public:
	virtual SsdFlushResult Flush();

protected:
	std::shared_ptr<ISsdController> _ssdController;
};

