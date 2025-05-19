#include "IoC.h"
#include "HelpCommand.h"
#include "HelpCommandMapper.h"

std::vector<std::shared_ptr<ICommandMapper>> IoC::GetCommandMappers()
{
	static std::shared_ptr<HelpCommand> helpCommand = std::make_shared<HelpCommand>();
	static std::shared_ptr<HelpCommandMapper> helpCommandMapper = std::make_shared<HelpCommandMapper>(helpCommand);

	return std::vector<std::shared_ptr<ICommandMapper>>{
		helpCommandMapper,
	};
}
