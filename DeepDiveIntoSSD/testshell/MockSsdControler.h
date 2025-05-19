#pragma once
#include <ostream>
#include <gmock/gmock-function-mocker.h>

#include "ISsdController.h"
#include "SsdReadService.h"

using namespace std;
using namespace testing;

class MockSsdController : public ISsdController
{
public:
	~MockSsdController() override = default;

public:
	MOCK_METHOD(SsdWriteResult, Write, (int, unsigned int), (override));
	MOCK_METHOD(SsdReadResult, Read, (int), (override));
};