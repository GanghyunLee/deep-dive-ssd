#pragma once
#include "ArgManager.h"

enum STATUS { CLEAN = 0, ERASED, MODIFIED };

class ICommandHandler {
public:
	virtual std::vector<Arg> handle(std::vector<Arg>& buffer,
		int cnt,
		const Arg& latestArg,
		int* tempStatus,
		int* status) = 0;
	virtual ~ICommandHandler() {}
};

class WriteCommandHandler : public ICommandHandler {
public:
	std::vector<Arg> handle(std::vector<Arg>& buffer, int cnt, const Arg& latestArg, int* tempStatus, int* status) override;

private:
	void modifyEraseCommand(Arg& eraseArg, const Arg& latestArg);
};
class EraseCommandHandler : public ICommandHandler {
public:
	std::vector<Arg> handle(std::vector<Arg>& buffer, int cnt, const Arg& latestArg, int* tempStatus, int* status) override;

private:
	bool isErased(const Arg& arg, int* status);
	bool isErasedBigger(const Arg& arg, int* status);
};