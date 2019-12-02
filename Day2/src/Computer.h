#ifndef DAY2_COMPUTER_H
#define DAY2_COMPUTER_H


#include <vector>

class Computer {
public:
	Computer(const std::vector<long> &data);
	void reset(const std::vector<long> &data);
	void run();
	long getOp(unsigned i);
	void setOp(unsigned i, long op);

private:
	unsigned pc = 0;
	std::vector<long> data;
};


#endif //DAY2_COMPUTER_H
