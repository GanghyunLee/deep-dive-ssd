#include "RunnerApplication.h"
#include <fstream>
#include <sstream>

#include "AbstractScriptCommand.h"
#include "ParsingUtil.h"

bool RunnerApplication::Run(int argc, char* argv[])
{
    try
    {
        std::string filename = argv[1];

        std::ifstream file(filename); // 파일 열기

        // 파일이 성공적으로 열렸는지 확인
        if (!file.is_open()) {
            std::stringstream ss;
            ss << "Cannot find the file " << filename << std::endl;
            throw std::exception{ss.str().c_str()};
        }

        // 파일에서 한줄씩 읽기
        std::string line;
        while (std::getline(file, line))
        {
            std::string lineLowerStr = ParsingUtil::ToLowerString(line);
            // 1. Find Matching Command (Only AbstractScriptCommand)
            std::shared_ptr<AbstractScriptCommand> command = std::dynamic_pointer_cast<AbstractScriptCommand>(
                FindMatchingCommand(lineLowerStr)
            );

            // 2. Check if Failed to map command
            if (command == nullptr)
            {
                std::stringstream ss;
                ss << "INVALID COMMAND(Your Command = " << line << ")" << std::endl;
                throw std::exception{ss.str().c_str()};
            }

            // 3. Print - ex) 1_FullWriteAndReadCompare  ___   Run...
            _logger->print("RunnerApplication", __FUNCTION__,
                command->GetCommandName() + "  ___  Run...");

            // 4. Execute Command
            std::shared_ptr<IView> view = command->Execute();

            // 5. Print Result(Pass / Fail)
            if (view)
                view->Render(_logger);

            _logger->printLine();

            // If the tc is failed, Runner must be stopped.
            if (command->GetScriptCommandResult() == false)
                break;
        }
    }
    catch (std::exception& ex)
    {
        _logger->print("RunnerApplication", __FUNCTION__, ex.what());
        return false;
    }

    return true;
}
