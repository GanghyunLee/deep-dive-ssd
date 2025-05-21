#include "HelpView.h"
#include <sstream>

void HelpView::Render(std::shared_ptr<ILogger>& logger)
{
    std::stringstream ss;
    ss << "* Team : DD(DeepDive)\n";
    ss << "* 팀장 : 이강현, * 팀원 : 권경민, 김민석, 이문형, 이재규\n";
    ss << "* Command Usage\n";
    ss << "- Write : write <lba> <data> (ex - write 3 0xABABABAB)\n";
    ss << "- Read : read <lba> (ex - read 3)\n";
    ss << "- Erase : erase <lba> <size> \n";
    ss << "- Erase(Range) : erase_range <startLba> <endLba>\n";
    ss << "- Flush : flush (ex - flush)\n";
    ss << "- Fullwrite : fullwrite <data> (ex - fullwrite 0xABABABAB)\n";
    ss << "- Fullread : fullread (ex - fullread)\n";
    ss << "- 1_FullWriteAndReadCompare\n";
    ss << "- 2_PartialLBAWrite\n";
    ss << "- 3_WriteReadAging\n";
    ss << "- 4_EraseAndWriteAging";

    logger->print("HelpView", __FUNCTION__, ss.str());
}
