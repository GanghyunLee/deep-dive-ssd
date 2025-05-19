#include "ReadView.h"

#include <iomanip>
#include <ostream>

void ReadView::Render(std::ostream& os)
{
	os << STR_PRINT_RESULT_PREFIX << " ";

	if (_readCommandResult.GetTestResult())
	{
		os << "LBA " << std::setw(2) << std::setfill('0') << _readCommandResult.GetLba() << " : ";
		os << "0x" << std::setw(8) << std::setfill('0') << std::hex << std::uppercase << static_cast<unsigned long long>(_readCommandResult.GetData());
	}
	else
	{
		os << "Error";
	}
}
