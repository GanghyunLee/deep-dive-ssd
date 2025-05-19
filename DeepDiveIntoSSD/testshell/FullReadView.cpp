#include "FullReadView.h"

#include <memory>
#include <iostream>

#include "ReadView.h"

void FullReadView::Render(std::ostream& os)
{
	for (const SsdReadResult& ssdReadResult : _readCommandResults)
	{
		std::shared_ptr<ReadView> readView = std::make_shared<ReadView>(ssdReadResult);
		readView->Render(os);
		os << std::endl;
	}
}
