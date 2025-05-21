#include "HelpView.h"
#include <sstream>

void HelpView::Render(std::shared_ptr<ILogger>& logger)
{
     std::stringstream ss;
     ss << "* Team : DD(DeepDive)\n";
     ss << "* 팀장 : 이강현, * 팀원 : 권경민, 김민석, 이문형, 이재규\n";
     ss << "* Command Usage\n";
     ss << "- write : ssd.exe W lba data (ex - ssd.exe W 3 0xABABABAB)\n";
     ss << "- read : ssd.exe R lba (ex - ssd.exe R 3)\n";
     ss << "- fullwrite : ssd.exe fullwrite data (ex - ssd.exe fullwrite 0xABABABAB)\n";
     ss << "- fullread : ssd.exe fullread (ex - ssd.exe fullread)\n";
     ss << "- 1_FullWriteAndReadCompare\n";
     ss << "- 2_PartialLBAWrite\n";
     ss << "- 3_WriteReadAging\n";
     ss << "- 4_EraseAndWriteAging";

     logger->print(STR_CLASS_NAME_HELPVIEW, __FUNCTION__, ss.str());
}
