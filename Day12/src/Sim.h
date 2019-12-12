#ifndef DAY12_SIM_H
#define DAY12_SIM_H


#include <vector>
#include "Moon.h"

class Sim {
public:
	Sim();

	Sim(const std::vector<Moon>& moons);

	void reset(const std::vector<Moon>& moons);

	bool matches(const std::vector<Moon>& moons) const;

	bool matches(unsigned comp, const std::vector<int>& positions, const std::vector<int>& velocities) const;

	void addMoon(const Moon& moon);

	unsigned long entropy();

	void step();

	int totalEnergy();

	void print();

	unsigned long noSteps() const;

private:

	void applyGravity();

	std::vector<unsigned> findCycles();

	std::vector<Moon> moons;

	unsigned long steps = 0;

};


#endif //DAY12_SIM_H
