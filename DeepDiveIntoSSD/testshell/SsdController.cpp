#include "SsdController.h"

SsdWriteResult SsdController::Write(int lba, unsigned int data)
{
	// TODO : Call ssd.exe, read ssd_output.txt
	return SsdWriteResult::From(true);
}
