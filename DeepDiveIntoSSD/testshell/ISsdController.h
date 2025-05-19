#pragma once
#include "SsdReadResult.h"
#include "SsdWriteResult.h"

class ISsdController
{
public:
	virtual ~ISsdController() = default;

public:
	virtual SsdWriteResult Write(int lba, unsigned int data) = 0;
	virtual SsdReadResult Read(int lba) = 0;
};

