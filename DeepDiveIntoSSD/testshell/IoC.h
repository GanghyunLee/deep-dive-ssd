#pragma once
#include <vector>

#include "ExitCommandMapper.h"

class ICommandMapper;



class IoC
{
public:
	IoC()
	{
		_exitCommandMapper = new ExitCommandMapper();
	}

	~IoC()
	{
		if (_exitCommandMapper == nullptr)
		{
			delete _exitCommandMapper;
			_exitCommandMapper = nullptr;
		}
	}

public:
	std::vector<ICommandMapper*> GetCommandMappers();

protected:
	ICommandMapper* _exitCommandMapper = nullptr;
};

