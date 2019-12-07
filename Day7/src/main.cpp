#include <iostream>
#include <vector>
#include <fstream>
#include <array>
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

std::vector<long> data;

long testSequence(std::vector<unsigned> phases, std::array<Computer*, 5> thrusters, bool feedback){


	std::vector<long> input;
	long output = 0;

	for(int i = 0; i < 5; i++){
		Computer* thruster = thrusters[i];
		thruster->reset(data);
		input = { phases[i], output };
		thruster->setInput(input);
		thruster->run();
		output = thruster->getOutput()[0];
		thruster->getOutput().clear();
	}

	if(feedback){
		while(!thrusters[4]->isHalted()){

			for(int i = 0; i < 5; i++){
				Computer* thruster = thrusters[i];
				input = { output };
				thruster->setInput(input);
				thruster->run();
				output = thruster->getOutput()[0];
				thruster->getOutput().clear();
			}
		}
	}

	return output;
}

bool sequenceDuplicates(std::vector<unsigned> phases){
	for(int i = 0; i < phases.size(); i++){
		for(int j = 0; j < phases.size(); j++){
			if(i == j) continue;
			if(phases[i] == phases[j]) return true;
		}
	}

	return false;
}

long testThrusters(std::array<Computer*, 5>& thrusters, unsigned rangeA, unsigned rangeB, bool feedback){
	long best = 0;

	for(unsigned i = rangeA; i <= rangeB; i++){
		for(unsigned j = rangeA; j <= rangeB; j++){
			for(unsigned k = rangeA; k <= rangeB; k++){
				for(unsigned l = rangeA; l <= rangeB; l++){
					for(unsigned m = rangeA; m <= rangeB; m++){
						std::vector<unsigned> phases = { i, j, k, l, m };
						if(sequenceDuplicates(phases)) continue;

						long result = testSequence(phases, thrusters, feedback);

						if(result > best) best = result;
					}
				}
			}
		}
	}

	return best;
}

int main(){
	data = loadData("../input.txt");

	std::array<Computer*, 5> thrusters { new Computer(data, BUFFER),
										new Computer(data, BUFFER),
										new Computer(data, BUFFER),
										new Computer(data, BUFFER),
										new Computer(data, BUFFER) };

	long best = testThrusters(thrusters, 0, 4, false);
	printf("Best (no feedback): %ld\n", best);

	best = testThrusters(thrusters, 5, 9, true);
	printf("Best (feedback): %ld\n", best);


	return 0;
}