#include <iostream>
#include <vector>
#include <fstream>
#include "Computer.h"
#include "Cabinet.h"
#include "Joystick.h"

std::vector<long> loadData(std::string path){
	std::ifstream file(path);
	std::string line;
	file >> line;

	std::vector<long> data;
	int last = 0;
	int next = 0;

	while((next = line.find(',', next+1)) != std::string::npos){
		std::string part = line.substr(last, next - last);

		if(part.empty()) continue;

		data.push_back(atol(part.data()));

		last = next+1;
	}

	data.push_back(atol(line.substr(last, line.size() - last).data()));

	return data;
}

int main(){
	std::vector<long> data = loadData("../input.txt");

	Computer computer(data, BUFFER);

	Cabinet cabinet(computer);
	computer.registerListener(&cabinet);

	computer.run();
	//cabinet.draw();

	printf("Blocks: %u\n", cabinet.count(Cabinet::BLOCK));

	computer.reset(data);
	cabinet.reset();
	computer.setOp(0, 2);
	computer.run();

	printf("Score: %u\n", cabinet.getScore());

	return 0;
}