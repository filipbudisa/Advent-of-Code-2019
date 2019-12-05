#ifndef DAY2_COMPUTER_H
#define DAY2_COMPUTER_H


#include <vector>
#include <queue>

enum ParameterMode {
	POSITION, IMMEDIATE
};

class Computer {
public:
	Computer(const std::vector<long> &data);
	void reset(const std::vector<long> &data);
	void run();
	long getOp(unsigned i);
	void setOp(unsigned i, long op);

private:
	void executeInstruction(unsigned opcode, std::vector<long>& data);

	unsigned pc = 0;
	std::vector<long> data;

	const unsigned OCParamCount[9];
};


#endif //DAY2_COMPUTER_H
