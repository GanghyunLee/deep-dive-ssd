#pragma once
#include <string>

#include "IView.h"
#include "WriteCommandResultDto.h"

class WriteView : public IView
{
public:
	WriteView(WriteCommandResultDto& writeCommandResult) : _writeCommandResult(writeCommandResult) { }
	~WriteView() override = default;

	void Render(std::ostream& os) override;

private:
	WriteCommandResultDto _writeCommandResult;
	const std::string STR_PRINT_RESULT_PREFIX = "[Write]";
};

