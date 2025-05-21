#include "FullWriteView.h"
#include <memory>
#include <iostream>

#include "WriteView.h"

void FullWriteView::Render(std::shared_ptr<ILogger>& logger)
{
	for (const SsdWriteResult& ssdWriteResult : _writeCommandResults)
	{
		std::shared_ptr<WriteView> writeView = std::make_shared<WriteView>(ssdWriteResult);
		writeView->Render(logger);
		logger->printLine();
	}
}
