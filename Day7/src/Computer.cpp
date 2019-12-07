#include <array>
#include "Computer.h"

Computer::Computer(const std::vector<long> &data) : data(data), OCParamCount { 0, 3, 3, 1, 1, 2, 2, 3, 3 } {

}

Computer::Computer(const std::vector<long> &data, InputMode iMode) : Computer(data) {
	Computer::iMode = iMode;
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
			if(executeInstruction(opcode, params)) return;
			continue;
		}

		pMode = (instruction - (instruction/10000) * 10000) / 1000 == 0 ? POSITION : IMMEDIATE;
		params.push_back((pMode == POSITION) ? data[data[pc+2]] : data[pc+2]);

		if(OCParamCount[opcode] == 2){
			if(executeInstruction(opcode, params)) return;
			continue;
		}

		pMode = instruction/10000 == 0 ? POSITION : IMMEDIATE;
		if(instruction > 10000){
			params.push_back(data[pc+3]);
		}else{
			params.push_back((pMode == POSITION) ? data[pc+3] : pc+3);
		}

		if(executeInstruction(opcode, params)) return;
	}

	halted = true;
}

bool Computer::executeInstruction(unsigned opcode, std::vector<long>& data){
	switch(opcode){
		case 1:
			setOp(data[2], data[0] + data[1]);
			break;
		case 2:
			setOp(data[2], data[0] * data[1]);
			break;
		case 3:
			long val;
			if(iMode == STD){
				printf("Input: ");
				scanf("%ld", &val);
			}else{
				if(input.empty()){
					halted = false;
					return true;
				}

				val = input.front();
				input.pop();
			}

			setOp(data[0], val);
			break;
		case 4:
			if(iMode == STD){
				printf("Output: %ld\n", data[0]);
			}else{
				output.push_back(data[0]);
			}
			break;
		case 5:
			if(data[0] != 0){
				pc = data[1];
				return false;
			}
			break;
		case 6:
			if(data[0] == 0){
				pc = data[1];
				return false;
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

	return false;
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
	while(!input.empty()) input.pop();
	output.clear();
}

void Computer::setInput(std::vector<long>& input){
	for(long u : input){
		Computer::input.push(u);
	}
}

std::vector<long>& Computer::getOutput(){
	return output;
}

bool Computer::isHalted() const{
	return halted;
}
