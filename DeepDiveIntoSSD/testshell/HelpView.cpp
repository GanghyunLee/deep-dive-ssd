#include "HelpView.h"
#include <sstream>

void HelpView::Render(std::shared_ptr<ILogger>& logger)
{
	std::stringstream ss;
	ss << "* Team : DD(DeepDive)" << std::endl;
	ss << "* 팀장 : 이강현, * 팀원 : 권경민, 김민석, 이문형, 이재규" << std::endl;
	ss << "* Command Usage" << std::endl;
	ss << "- write : ssd.exe W lba data (ex - ssd.exe W 3 0xABABABAB)" << std::endl;
	ss << "- read : ssd.exe R lba (ex - ssd.exe R 3)" << std::endl;
	ss << "- fullwrite : ssd.exe fullwrite data (ex - ssd.exe fullwrite 0xABABABAB)" << std::endl;
	ss << "- fullread : ssd.exe fullread (ex - ssd.exe fullread)" << std::endl;
	ss << "- 1_FullWriteAndReadCompare" << std::endl;
	ss << "- 2_PartialLBAWrite" << std::endl;
	ss << "- 3_WriteReadAging";
	ss << "- 4_EraseAndWriteAging";

	logger->print("HelpView", __FUNCTION__, ss.str());
}
