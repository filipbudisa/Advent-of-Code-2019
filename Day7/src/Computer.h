#ifndef DAY2_COMPUTER_H
#define DAY2_COMPUTER_H


#include <vector>
#include <queue>

enum InputMode {
	STD, BUFFER
};

enum ParameterMode {
	POSITION, IMMEDIATE
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

private:
	bool executeInstruction(unsigned opcode, std::vector<long>& data);

	unsigned pc = 0;
	std::vector<long> data;
	bool halted = true;

	const unsigned OCParamCount[9];

	InputMode iMode = STD;
	std::queue<long> input;
	std::vector<long> output;
};


#endif //DAY2_COMPUTER_H
