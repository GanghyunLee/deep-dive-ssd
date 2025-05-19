#pragma once
#include <vector>

#include "IView.h"
#include "SsdReadResult.h"

class FullReadView : public IView
{
public:
	FullReadView(const std::vector<SsdReadResult>& readCommandResults) : _readCommandResults(readCommandResults) {}
	~FullReadView() override = default;

	void Render(std::ostream& os) override;

private:
	std::vector<SsdReadResult> _readCommandResults;
};
