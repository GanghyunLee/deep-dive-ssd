#include "SsdController.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>

SsdWriteResult SsdController::Write(int lba, unsigned int data)
{
	std::stringstream ss;
    ss << "ssd.exe write " << lba << " 0x" << ToUpperHex(data);

    std::string cmd = ss.str();
    ExecuteCommand(cmd);

    std::string input = ReadFileToString("ssd_output.txt");
	return SsdWriteResult::From(input.empty());
}

std::string SsdController::ExecuteCommand(const std::string& cmd)
{
    // "cmd /c cd" 명령어를 사용하여 현재 디렉토리 경로를 가져옵니다.
    char buffer[128];
    std::string result = "";

    // popen을 사용하여 "cmd /c cd" 명령을 실행하고 그 출력을 받음
    std::shared_ptr<FILE> pipe(_popen(cmd.c_str(), "r"), _pclose);

    if (!pipe) {
        throw std::exception("Failed to open pipe.");
    }

    // 명령어 출력 결과를 읽어서 result에 저장
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    // 출력에서 마지막의 '\n'을 제거
    if (!result.empty() && result[result.length() - 1] == '\n') {
        result.pop_back();
    }

    return result;
}

std::string SsdController::ToUpperHex(unsigned int value)
{
    std::stringstream ss;
    ss << std::uppercase << std::hex << value;  // 대문자 16진수로 변환
    return ss.str();
}

std::string SsdController::ReadFileToString(const std::string& filename)
{
    std::ifstream file(filename);  // 파일을 읽기 모드로 열기
    if (!file.is_open()) {
        std::stringstream errSs;
        errSs << "Failed to open file: " << filename;
        throw std::exception{ errSs.str().c_str() };
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // 파일 내용을 문자열 스트림으로 읽기

    return buffer.str();  // 문자열로 반환
}
