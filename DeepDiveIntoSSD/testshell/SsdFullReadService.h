#pragma once
#include <memory>
#include <vector>

#include "ISsdController.h"

class SsdFullReadService
{
	enum
	{
		MAX_LBA = 99
	};

public:
	SsdFullReadService(std::shared_ptr<ISsdController> ssdController) : _ssdController(ssdController)
	{
	}

	virtual ~SsdFullReadService() = default;

public:
	virtual std::vector<SsdReadResult> FullRead();

protected:
	std::shared_ptr<ISsdController> _ssdController;
};

