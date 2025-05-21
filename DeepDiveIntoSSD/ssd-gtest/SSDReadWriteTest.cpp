#include "gmock/gmock.h"
#include "Ssd.h"

using namespace testing;

class SSDFixture : public Test {
public:
	const std::string WRITE_SUCCESS_RESULT = "";

	SSD* ssdReal = &SSD::getInstance();
};

//TEST_F(SSDFixture, initSSDNANDTXTfile) {
//	std::fstream fp("ssd_nand.txt", std::ios::in);
//	int lineNum = 0;
//	std::string line;
//	
//	while (std::getline(fp, line)) {
//		lineNum++;
//	}
//	fp.close();
//	EXPECT_EQ(lineNum, 100);
//}

TEST_F(SSDFixture, readSSDNANDTextFileAfterInit) {
	ssdReal->read(0);

	std::fstream fp("ssd_output.txt", std::ios::in);
	std::string line;

	std::getline(fp, line);
	fp.close();

	EXPECT_EQ("0x00000000", line);
	
}

TEST_F(SSDFixture, writeSSDNANDTextFile) {

	ssdReal->write(40, "0x00000033");

	std::fstream fp("ssd_output.txt", std::ios::in);
	std::string line;

	std::getline(fp, line);
	fp.close();

	EXPECT_EQ(WRITE_SUCCESS_RESULT, line);

}

TEST_F(SSDFixture, writeInvalidAddressFile) {

	ssdReal->write(100, "0x00000033");

	std::fstream fp("ssd_output.txt", std::ios::in);
	std::string line;

	std::getline(fp, line);
	fp.close();

	EXPECT_EQ("ERROR", line);

}

TEST_F(SSDFixture, readInvalidAddressFile) {

	ssdReal->read(100);

	std::fstream fp("ssd_output.txt", std::ios::in);
	std::string line;

	std::getline(fp, line);
	fp.close();
	EXPECT_EQ("ERROR", line);

}

TEST_F(SSDFixture, eraseOutOfRangeTest) {

	ssdReal->erase(10, "11");

	std::fstream fp("ssd_output.txt", std::ios::in);
	std::string line;

	std::getline(fp, line);
	EXPECT_EQ("ERROR", line);
	fp.close();
}

TEST_F(SSDFixture, eraseValidRangeTest) {

	ssdReal->erase(10, "1");

	std::fstream fp("ssd_output.txt", std::ios::in);
	std::string line;

	std::getline(fp, line);
	EXPECT_EQ("", line);
	fp.close();
}

TEST_F(SSDFixture, eraseNothingTest) {

	ssdReal->erase(10, "0");

	std::fstream fp("ssd_output.txt", std::ios::in);
	std::string line;

	std::getline(fp, line);
	EXPECT_EQ("", line);
	fp.close();
}