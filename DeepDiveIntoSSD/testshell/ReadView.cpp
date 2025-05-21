#include "ReadView.h"

#include <iomanip>
#include <sstream>

void ReadView::Render(std::shared_ptr<ILogger>& logger)
{
	std::stringstream ss;
	ss << STR_PRINT_RESULT_PREFIX << " ";

	if (_readCommandResult.GetTestResult())
	{
		ss << "LBA " << std::setw(2) << std::setfill('0') << _readCommandResult.GetLba() << " : ";
		ss << "0x" << std::setw(8) << std::setfill('0') << std::hex << std::uppercase << static_cast<unsigned long long>(_readCommandResult.GetData());
	}
	else
	{
		ss << STR_PRINT_RESULT_ERROR;
	}

	logger->print(STR_CLASS_NAME_READVIEW, __FUNCTION__, ss.str());
}
