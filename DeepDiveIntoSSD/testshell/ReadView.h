#pragma once
#include <string>

#include "IView.h"
#include "SsdReadResult.h"

class ReadView : public IView
{
public:
	ReadView(const SsdReadResult& readCommandResult) : _readCommandResult(readCommandResult) {}
	~ReadView() override = default;

	void Render(std::ostream& os) override;

private:
	SsdReadResult _readCommandResult;
	const std::string STR_PRINT_RESULT_PREFIX = "[Read]";
};
