#include "FullReadView.h"

#include <memory>
#include <iostream>

#include "ReadView.h"

void FullReadView::Render(std::shared_ptr<ILogger>& logger)
{
	for (const SsdReadResult& ssdReadResult : _readCommandResults)
	{
		std::shared_ptr<ReadView> readView = std::make_shared<ReadView>(ssdReadResult);
		readView->Render(logger);
		logger->printLine();
	}
}
