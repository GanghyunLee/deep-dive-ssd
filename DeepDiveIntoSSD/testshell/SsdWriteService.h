#pragma once
#include "ISsdController.h"

class SsdWriteService
{
public:
	SsdWriteService(ISsdController* ssdController) : _ssdController(ssdController)
	{
	}

public:
	SsdWriteResult Write(int lba, unsigned int data);

protected:
	ISsdController* _ssdController;
};

