#ifndef DAY2_COMPUTER_H
#define DAY2_COMPUTER_H


#include <vector>
#include <queue>
#include "IComputerListener.h"

enum InputMode {
	STD, BUFFER
};

enum ParameterMode {
	POSITION, IMMEDIATE, RELATIVE
};

class Computer {
public:
	Computer(const std::vector<long> &data);
	Computer(const std::vector<long> &data, InputMode iMode);
	void reset(const std::vector<long> &data);
	void run();
	long getOp(unsigned i);
	void setOp(unsigned i, long op);

	void setInput(std::vector<long>& input);
	std::vector<long>& getOutput();

	bool isHalted() const;

	void registerListener(IComputerListener* listener);

private:
	bool executeInstruction(unsigned opcode, std::vector<long>& data);
	ParameterMode determinepMode(int instruction, int pos);
	long determineParam(long op, ParameterMode pMode);

	unsigned pc = 0;
	std::vector<long> data;
	bool halted = true;
	long relativeBase = 0;

	const unsigned OCParamCount[10];

	InputMode iMode = STD;
	std::queue<long> input;
	std::vector<long> output;

	IComputerListener* listener;
};


#endif //DAY2_COMPUTER_H
