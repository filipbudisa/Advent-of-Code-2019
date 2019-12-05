#include <array>
#include "Computer.h"

Computer::Computer(const std::vector<long> &data) : data(data), OCParamCount({ 0, 3, 3, 1, 1, 2, 2, 3, 3 }) {

}

void Computer::run(){
	int instruction, opcode;
	std::vector<long> params;
	ParameterMode pMode;

	while((instruction = data[pc]) != 99){
		params.clear();
		opcode = instruction - (instruction/100) * 100;

		pMode = (instruction - (instruction/1000) * 1000) / 100 == 0 ? POSITION : IMMEDIATE;
		params.push_back((opcode != 3 && pMode == POSITION) ? data[data[pc+1]] : data[pc+1]);

		if(OCParamCount[opcode] == 1){
			executeInstruction(opcode, params);
			continue;
		}

		pMode = (instruction - (instruction/10000) * 10000) / 1000 == 0 ? POSITION : IMMEDIATE;
		params.push_back((pMode == POSITION) ? data[data[pc+2]] : data[pc+2]);

		if(OCParamCount[opcode] == 2){
			executeInstruction(opcode, params);
			continue;
		}

		pMode = instruction/10000 == 0 ? POSITION : IMMEDIATE;
		if(instruction > 10000){
			params.push_back(data[pc+3]);
		}else{
			params.push_back((pMode == POSITION) ? data[pc+3] : pc+3);
		}

		executeInstruction(opcode, params);
	}
}

void Computer::executeInstruction(unsigned opcode, std::vector<long>& data){
	switch(opcode){
		case 1:
			setOp(data[2], data[0] + data[1]);
			break;
		case 2:
			setOp(data[2], data[0] * data[1]);
			break;
		case 3:
			long val;
			printf("Input: ");
			scanf("%ld", &val);
			setOp(data[0], val);
			break;
		case 4:
			printf("Output: %ld\n", data[0]);
			break;
		case 5:
			if(data[0] != 0){
				pc = data[1];
				return;
			}
			break;
		case 6:
			if(data[0] == 0){
				pc = data[1];
				return;
			}
			break;
		case 7:
			setOp(data[2], data[0] < data[1]);
			break;
		case 8:
			setOp(data[2], data[0] == data[1]);
			break;
	}

	pc += OCParamCount[opcode] + 1;
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