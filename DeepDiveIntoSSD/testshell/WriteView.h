#pragma once
#include <string>

#include "IView.h"
#include "SsdWriteResult.h"

class WriteView : public IView
{
public:
	WriteView(const SsdWriteResult& writeCommandResult) : _writeCommandResult(writeCommandResult) { }
	~WriteView() override = default;

	void Render(std::ostream& os) override;

private:
	SsdWriteResult _writeCommandResult;
	const std::string STR_PRINT_RESULT_PREFIX = "[Write]";
};

