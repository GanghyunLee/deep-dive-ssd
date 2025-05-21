#include "IoC.h"

#include "EraseAndWriteAgingTestScriptCommandMapper.h"
#include "EraseCommandMapper.h"
#include "EraseRangeCommandMapper.h"
#include "FlushCommandMapper.h"
#include "FullReadCommandMapper.h"
#include "FullWriteAndReadCompareTestScriptCommandMapper.h"
#include "FullWriteCommandMapper.h"
#include "HelpCommand.h"
#include "HelpCommandMapper.h"
#include "PartialLBAWriteTestScriptCommandMapper.h"
#include "ReadCommandMapper.h"
#include "SsdController.h"
#include "WriteCommand.h"
#include "WriteCommandMapper.h"
#include "WriteReadAgingTestScriptCommandMapper.h"

std::vector<std::shared_ptr<ICommandMapper>> IoC::GetCommandMappers()
{
	static std::shared_ptr<WriteCommandMapper> writeCommandMapper = std::make_shared<WriteCommandMapper>([&](int lba, unsigned int data)
	{
		return std::make_shared<WriteCommand>(GetSsdWriteService(), lba, data);
	});

	static std::shared_ptr<ReadCommandMapper> readCommandMapper = std::make_shared<ReadCommandMapper>([&](int lba)
		{
			return std::make_shared<ReadCommand>(GetSsdReadService(), lba);
		});

	static std::shared_ptr<FullWriteCommandMapper> fullWriteCommandMapper = std::make_shared<FullWriteCommandMapper>([&](unsigned int data)
		{
			return std::make_shared<FullWriteCommand>(GetSsdFullWriteService(), data);
		});

	static std::shared_ptr<FullReadCommandMapper> fullReadCommandMapper = std::make_shared<FullReadCommandMapper>([&]()
		{
			return std::make_shared<FullReadCommand>(GetSsdFullReadService());
		});

	static std::shared_ptr<EraseCommandMapper> eraseCommandMapper = std::make_shared<EraseCommandMapper>(GenerateEraseCommandFactory());
	static std::shared_ptr<EraseRangeCommandMapper> eraseRangeCommandMapper = std::make_shared<EraseRangeCommandMapper>(GenerateEraseCommandFactory());

	static std::shared_ptr<FullWriteAndReadCompareTestScriptCommandMapper> fullWriteAndReadCompareTestScriptCommandMapper =
		std::make_shared<FullWriteAndReadCompareTestScriptCommandMapper>(GetFullWriteAndReadCompareTestScriptService());

	static std::shared_ptr<PartialLBAWriteTestScriptCommandMapper> partialLBAWriteTestScriptCommandMapper =
		std::make_shared<PartialLBAWriteTestScriptCommandMapper>(GetPartialLbaWriteTestScriptService());

	static std::shared_ptr<WriteReadAgingTestScriptCommandMapper> writeReadAgingTestScriptCommandMapper =
		std::make_shared<WriteReadAgingTestScriptCommandMapper>(GetWriteReadAgingTestScriptService());

	static std::shared_ptr<EraseAndWriteAgingTestScriptCommandMapper> eraseAndWriteAgingTestScriptCommandMapper =
		std::make_shared<EraseAndWriteAgingTestScriptCommandMapper>(GetEraseAndWriteAgingTestScriptService());

	static std::shared_ptr<HelpCommand> helpCommand = std::make_shared<HelpCommand>();
	static std::shared_ptr<HelpCommandMapper> helpCommandMapper = std::make_shared<HelpCommandMapper>(helpCommand);

	static std::shared_ptr<FlushCommand> flushCommand = std::make_shared<FlushCommand>(GetSsdFlushService());
	static std::shared_ptr<FlushCommandMapper> flushCommandMapper = std::make_shared<FlushCommandMapper>(flushCommand);

	return std::vector<std::shared_ptr<ICommandMapper>>{
		writeCommandMapper,
		readCommandMapper,
		flushCommandMapper,
		fullWriteCommandMapper,
		fullReadCommandMapper,
		fullWriteAndReadCompareTestScriptCommandMapper,
		partialLBAWriteTestScriptCommandMapper,
		writeReadAgingTestScriptCommandMapper,
		eraseAndWriteAgingTestScriptCommandMapper,
		helpCommandMapper,
		eraseCommandMapper,
		eraseRangeCommandMapper,
	};
}

std::shared_ptr<SsdWriteService> IoC::GetSsdWriteService()
{
	static std::shared_ptr<SsdWriteService> ssdWriteService = std::make_shared<SsdWriteService>(GetSsdController());
	return ssdWriteService;
}

std::shared_ptr<SsdReadService> IoC::GetSsdReadService()
{
	static std::shared_ptr<SsdReadService> ssdReadService = std::make_shared<SsdReadService>(GetSsdController());
	return ssdReadService;
}

std::shared_ptr<SsdFullWriteService> IoC::GetSsdFullWriteService()
{
	static std::shared_ptr<SsdFullWriteService> ssdFullWriteService = std::make_shared<SsdFullWriteService>(GetSsdController());
	return ssdFullWriteService;
}

std::shared_ptr<SsdFullReadService> IoC::GetSsdFullReadService()
{
	static std::shared_ptr<SsdFullReadService> ssdFullReadService = std::make_shared<SsdFullReadService>(GetSsdController());
	return ssdFullReadService;
}

std::shared_ptr<SsdEraseService> IoC::GetSsdEraseService()
{
	static std::shared_ptr<SsdEraseService> ssdEraseService = std::make_shared<SsdEraseService>(GetSsdController());
	return ssdEraseService;
}

std::shared_ptr<SsdFlushService> IoC::GetSsdFlushService()
{
	static std::shared_ptr<SsdFlushService> ssdFlushService = std::make_shared<SsdFlushService>(GetSsdController());
	return ssdFlushService;
}

std::shared_ptr<FullWriteAndReadCompareTestScriptService> IoC::GetFullWriteAndReadCompareTestScriptService()
{
	static std::shared_ptr<FullWriteAndReadCompareTestScriptService> ssdScriptService = 
		std::make_shared<FullWriteAndReadCompareTestScriptService>(GetSsdController());
	return ssdScriptService;
}

std::shared_ptr<PartialLbaWriteTestScriptService> IoC::GetPartialLbaWriteTestScriptService()
{
	static std::shared_ptr<PartialLbaWriteTestScriptService> ssdScriptService =
		std::make_shared<PartialLbaWriteTestScriptService>(GetSsdController());
	return ssdScriptService;
}

std::shared_ptr<WriteReadAgingTestScriptService> IoC::GetWriteReadAgingTestScriptService()
{
	static std::shared_ptr<WriteReadAgingTestScriptService> ssdScriptService =
		std::make_shared<WriteReadAgingTestScriptService>(GetSsdController());
	return ssdScriptService;
}

std::shared_ptr<EraseAndWriteAgingTestScriptService> IoC::GetEraseAndWriteAgingTestScriptService()
{
	static std::shared_ptr<EraseAndWriteAgingTestScriptService> ssdScriptService =
		std::make_shared<EraseAndWriteAgingTestScriptService>(GetSsdController());
	return ssdScriptService;
}

std::shared_ptr<ISsdController> IoC::GetSsdController()
{
	static std::shared_ptr<ISsdController> ssdController = std::make_shared<SsdController>();
	return ssdController;
}

EraseCommandFactory IoC::GenerateEraseCommandFactory()
{
	return [&](int lba, int size)
	{
		return std::make_shared<EraseCommand>(GetSsdEraseService(), lba, size);
	};
}
