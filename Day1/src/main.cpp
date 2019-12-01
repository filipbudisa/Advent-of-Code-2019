#include <iostream>
#include <fstream>

int fuelMass(int weight){
	return (weight/3) - 2;
}

int main(){
	std::ifstream input("../input.txt");

	int totalFuel = 0;
	int fuelFuel = 0;

	std::string line;
	while(input >> line){
		int weight = atoi(line.data());
		int fuel = fuelMass(weight);
		totalFuel += std::max(0, fuel);

		while(fuel > 0){
			fuel = fuelMass(fuel);
			fuelFuel += std::max(0, fuel);
		}
	}

	printf("Total fuel for input: %d\n", totalFuel);
	printf("Total fuel part two: %d\n", totalFuel + fuelFuel);
}