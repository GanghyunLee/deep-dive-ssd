#include "IoC.h"
#include "HelpCommand.h"
#include "HelpCommandMapper.h"
#include "SsdController.h"
#include "WriteCommand.h"
#include "WriteCommandMapper.h"

std::vector<std::shared_ptr<ICommandMapper>> IoC::GetCommandMappers()
{
	static std::shared_ptr<WriteCommandMapper> writeCommandMapper = std::make_shared<WriteCommandMapper>([&](int lba, unsigned int data)
	{
		return std::make_shared<WriteCommand>(GetSsdWriteService(), lba, data);
	});

	static std::shared_ptr<HelpCommand> helpCommand = std::make_shared<HelpCommand>();
	static std::shared_ptr<HelpCommandMapper> helpCommandMapper = std::make_shared<HelpCommandMapper>(helpCommand);

	return std::vector<std::shared_ptr<ICommandMapper>>{
		writeCommandMapper,
		helpCommandMapper,
	};
}

std::shared_ptr<SsdWriteService> IoC::GetSsdWriteService()
{
	static std::shared_ptr<SsdWriteService> ssdWriteService = std::make_shared<SsdWriteService>(GetSsdController());
	return ssdWriteService;
}

std::shared_ptr<ISsdController> IoC::GetSsdController()
{
	static std::shared_ptr<ISsdController> ssdController = std::make_shared<SsdController>();
	return ssdController;
}
