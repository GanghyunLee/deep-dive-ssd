#include "FullWriteView.h"
#include <memory>
#include <iostream>

#include "WriteView.h"

void FullWriteView::Render(std::ostream& os)
{
	for (const SsdWriteResult& ssdWriteResult : _writeCommandResults)
	{
		std::shared_ptr<WriteView> writeView = std::make_shared<WriteView>(ssdWriteResult);
		writeView->Render(os);
		os << std::endl;
	}
}
