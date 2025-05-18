#include "IoC.h"
#include "ExitCommandMapper.h"

std::vector<ICommandMapper*> IoC::GetCommandMappers()
{
	return std::vector<ICommandMapper*>{
		_exitCommandMapper
	};
}
