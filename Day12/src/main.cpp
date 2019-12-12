#include <iostream>
#include <vector>
#include <fstream>
#include "Moon.h"
#include "Sim.h"

std::vector<Moon> loadMoons(const std::string& path){
	std::ifstream file(path);
	std::string pos;

	std::vector<Moon> moons;
	Vector moonPosition;

	while(file >> pos){
		bool last = false;

		int max = pos.find(',');
		if(max == std::string::npos){
			max = pos.find('>');
			last = true;
		}

		int min = pos.find('=') + 1;

		std::string val = pos.substr(min, max - min);
		moonPosition.push_back(std::atoi(val.data()));

		if(last){
			moons.emplace_back(moonPosition);
			moonPosition.clear();
		}
	}

	return moons;
}

int main(){
	std::vector<Moon> moons = loadMoons("../input.txt");

	Sim sim(moons);

	for(int i = 0; i < 1000; i++){
		sim.step();
		//sim.print();
	}

	printf("E = %d\n\n", sim.totalEnergy());

	sim.reset(moons);

	unsigned long entropy = sim.entropy();
	printf("%lu steps to reverse entropy\n", entropy);

	return 0;
}