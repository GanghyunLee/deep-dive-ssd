#include "HelpView.h"
#include <iostream>

void HelpView::Render(std::ostream& os)
{
	os << "* Team : DD(DeepDive)" << std::endl;
	os << "* 팀장 : 이강현, * 팀원 : 권경민, 김민석, 이문형, 이재규" << std::endl;
	os << "* Command Usage" << std::endl;
	os << "- write : ssd.exe W lba data (ex - ssd.exe W 3 0xABABABAB)" << std::endl;
	os << "- read : ssd.exe R lba (ex - ssd.exe R 3)" << std::endl;
	os << "- fullwrite : ssd.exe fullwrite data (ex - ssd.exe fullwrite 0xABABABAB)" << std::endl;
	os << "- fullread : ssd.exe fullread (ex - ssd.exe fullread)" << std::endl;
	os << "- 1_FullWriteAndReadCompare" << std::endl;
	os << "- 2_PartialLBAWrite" << std::endl;
	os << "- 3_WriteReadAging";
}
