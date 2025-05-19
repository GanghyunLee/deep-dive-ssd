#pragma once
#include "ISsdController.h"

class SsdController : public ISsdController
{
public:
	SsdWriteResult Write(int lba, unsigned int data) override;
};

