#pragma once
#include "SsdEraseResult.h"
#include "SsdFlushResult.h"
#include "SsdReadResult.h"
#include "SsdWriteResult.h"

class ISsdController
{
public:
	virtual ~ISsdController() = default;

public:
	virtual SsdWriteResult Write(int lba, unsigned int data) = 0;
	virtual SsdReadResult Read(int lba) = 0;
	virtual SsdEraseResult Erase(int lba, int size) = 0;
	virtual SsdFlushResult Flush() = 0;
};

