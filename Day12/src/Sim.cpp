#include <cstdio>
#include <numeric>
#include "Sim.h"

Sim::Sim(){

}

Sim::Sim(const std::vector<Moon>& moons) : moons(moons){

}

void Sim::reset(const std::vector<Moon>& moons){
	Sim::moons = moons;
	steps = 0;
}

void Sim::addMoon(const Moon& moon){
	moons.push_back(moon);
}

void Sim::applyGravity(){

	for(Moon& m1 : moons){
		for(Moon& m2 : moons){
			if(&m1 == &m2) break;

			Vector d1;
			Vector d2;

			const Vector& p1 = m1.getPosition();
			const Vector& p2 = m2.getPosition();

			for(int i = 0; i < p1.size(); i++){
				if(p1[i] < p2[i]){
					d1.push_back(1);
					d2.push_back(-1);
				}else if(p1[i] > p2[i]){
					d1.push_back(-1);
					d2.push_back(1);
				}else{
					d1.push_back(0);
					d2.push_back(0);
				}
			}

			m1.addVelocity(d1);
			m2.addVelocity(d2);
		}
	}
}

void Sim::step(){
	applyGravity();

	for(Moon& moon : moons){
		moon.step();
	}

	steps++;
}

int Sim::totalEnergy(){
	int sum = 0;

	for(const Moon& m : moons){
		sum += m.energyTotal();
	}

	return sum;
}

void Sim::print(){
	printf("After %d steps:\n", steps);
	printf("E = %d\n\n", totalEnergy());

	for(const Moon& moon : moons){
		moon.print();
	}

	printf("\n");
}

bool Sim::matches(const std::vector<Moon>& moons) const{
	if(moons.size() != Sim::moons.size()) return false;

	for(int i = 0; i < moons.size(); i++){
		if(!Sim::moons[i].matches(moons[i])){
			return false;
		}
	}

	return true;
}

bool Sim::matches(unsigned comp, const std::vector<int>& positions, const std::vector<int>& velocities) const{

	for(int i = 0; i < moons.size(); i++){
		const Moon& m = moons[i];

		if(m.getPosition()[comp] != positions[i] || m.getVelocity()[comp] != velocities[i]){
			return false;
		}
	}

	return true;
}

unsigned long Sim::noSteps() const{
	return steps;
}

std::vector<unsigned> Sim::findCycles(){
	std::vector<unsigned> cycles;

	for(int i = 0; i < moons[0].getPosition().size(); i++){
		std::vector<int> targetPositions;
		std::vector<int> targetVelocities;

		for(const Moon& m : moons){
			targetPositions.push_back(m.getPosition()[i]);
			targetVelocities.push_back(m.getVelocity()[i]);
		}

		unsigned steps = 0;

		do {
			for(Moon& m1 : moons){
				for(Moon& m2 : moons){
					if(&m1 == &m2) break;

					int p1 = m1.getPosition()[i];
					int p2 = m2.getPosition()[i];

					int d1 = 0;
					int d2 = 0;

					if(p1 < p2){
						d1 = 1;
						d2 = -1;
					}else if(p1 > p2){
						d1 = -1;
						d2 = 1;
					}

					Vector v1;
					v1.resize(m1.getPosition().size());
					Vector v2;
					v2.resize(m2.getPosition().size());

					v1[i] = d1;
					v2[i] = d2;

					m1.addVelocity(v1);
					m2.addVelocity(v2);
				}
			}

			if(matches(i, targetPositions, targetVelocities)){
				break;
			}

			for(Moon& m : moons){
				m.stepComp(i);
			}

			steps++;
		} while(true);

		printf("%d. component cycle: %d\n", i+1, steps);
		cycles.push_back(steps);
	}

	for(int i = 0; i < cycles.size(); i++){
		cycles[i] += 1;
	}

	return cycles;
}

unsigned long Sim::entropy(){
	std::vector<unsigned> cycles = findCycles();

	unsigned long l = cycles[0];

	for(int i = 1; i < cycles.size(); i++){
		l = std::lcm(l, cycles[i]);
	}

	return l;
}
