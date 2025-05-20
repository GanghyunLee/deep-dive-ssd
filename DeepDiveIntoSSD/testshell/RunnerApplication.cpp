#include "RunnerApplication.h"
#include <fstream>
#include <sstream>

bool RunnerApplication::Run(int argc, char* argv[])
{
    try
    {
        std::string filename = argv[1];

        std::ifstream file(filename); // 파일 열기

        // 파일이 성공적으로 열렸는지 확인
        if (!file.is_open()) {
            std::stringstream ss;
            ss << "파일을 열 수 없습니다: " << filename;
            throw std::exception{ss.str().c_str()};
        }

        // 파일에서 한줄씩 읽기
        std::string line;
        while (std::getline(file, line))
        {
            InterpretUserCommandAndExecute(line);
        }
    }
    catch (std::exception& ex)
    {
        _oStream << ex.what();
        return false;
    }

    return true;
}
