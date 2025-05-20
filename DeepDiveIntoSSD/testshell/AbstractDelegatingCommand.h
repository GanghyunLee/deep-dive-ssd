#pragma once
#include <vector>

#include "ICommand.h"

class AbstractDelegatingCommand : public ICommand
{
public:
	explicit AbstractDelegatingCommand(const std::vector<std::shared_ptr<ICommand>>& commands) : _commands(commands) { }
	~AbstractDelegatingCommand() override = default;

	std::vector<std::shared_ptr<ICommand>> GetCommands() { return _commands; }

protected:
	std::vector<std::shared_ptr<ICommand>> _commands;
};
