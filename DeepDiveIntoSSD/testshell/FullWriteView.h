#pragma once
#include <string>
#include <vector>
#include "IView.h"
#include "SsdWriteResult.h"

class FullWriteView : public IView
{
public:
	FullWriteView(const std::vector<SsdWriteResult>& writeCommandResults) : _writeCommandResults(writeCommandResults) {}
	~FullWriteView() override = default;

	void Render(std::ostream& os) override;

private:
	std::vector<SsdWriteResult> _writeCommandResults;
};

