#include "Computer.h"

Computer::Computer(const std::vector<long> &data) : data(data){}

void Computer::run(){
	int opcode;

	while((opcode = data[pc]) != 99){
		switch(opcode){
			case 1:
				setOp(data[pc+3], data[data[pc+1]] + data[data[pc+2]]);
				pc += 4;
				break;
			case 2:
				setOp(data[pc+3], data[data[pc+1]] * data[data[pc+2]]);
				pc += 4;
				break;
			/*default:
				pc++;*/
		}
	}
}

long Computer::getOp(unsigned i){
	if(i >= data.size()) return -1;
	return data[i];
}

void Computer::setOp(unsigned i, long op){
	if(i >= data.size()) data.resize(i+1);
	data[i] = op;
}

void Computer::reset(const std::vector<long> &_data){
	data = _data;
	pc = 0;
}
