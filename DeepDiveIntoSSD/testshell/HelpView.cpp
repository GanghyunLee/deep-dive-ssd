#include "HelpView.h"
#include <iostream>

void HelpView::Render(std::ostream& os)
{
	os << "Team : DD(DeepDive)" << std::endl;
	os << "writer : �̰���, �ǰ��, ��μ�, �̹���, �����" << std::endl;
	os << "write : ssd.exe W lba address" << std::endl;
	os << "read : ssd.exe R address" << std::endl;
	os << "fullwrite : ssd.exe fullwrite 0xABCDFFFF" << std::endl;
	os << "fullread : ssd.exe fullread 0xABCDFFFF";
}
