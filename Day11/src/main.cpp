#include <iostream>
#include <set>
#include <fstream>
#include "Computer.h"
#include "Robot.h"

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
	Computer c(data, BUFFER);
	Robot robot(c);

	c.run();
	unsigned hullPainted = robot.hullPainted();
	robot.print();
	robot.printPainted();

	c.reset(data);
	robot.reset();

	robot.paint(1);
	c.run();

	printf("\n[ %d ]\n", hullPainted);
	robot.print();

	return 0;
}