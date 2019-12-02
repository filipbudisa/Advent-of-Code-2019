#include <iostream>
#include <fstream>
#include <vector>
#include "Computer.h"

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

	Computer c(data);
	c.setOp(1, 12);
	c.setOp(2, 2);
	c.run();

	printf("Pos 0: %ld\n", c.getOp(0));

	for(int i = 0; i <= 99; i++){
		for(int j = 0; j <= 99; j++){
			c.reset(data);

			c.setOp(1, i);
			c.setOp(2, j);
			c.run();

			if(c.getOp(0) == 19690720){
				printf("[ %d ]\n", 100* i + j);
			}
		}
	}
}