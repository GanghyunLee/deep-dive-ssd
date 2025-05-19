#pragma once
#include "SsdWriteResult.h"

class ISsdController
{
public:
	virtual ~ISsdController() = default;

public:
	virtual SsdWriteResult Write(int lba, unsigned int data) = 0;
};

