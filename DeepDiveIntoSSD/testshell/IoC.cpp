#include "IoC.h"

#include "HelpCommand.h"
#include "HelpCommandMapper.h"
#include "HelpView.h"

std::vector<ICommandMapper*> IoC::GetCommandMappers()
{
	static HelpView helpView{};
	static HelpCommand helpCommand{ &helpView };
	static HelpCommandMapper helpCommandMapper{ &helpCommand };

	return std::vector<ICommandMapper*>{
		&helpCommandMapper,
	};
}
