#ifndef DAY12_MOON_H
#define DAY12_MOON_H


#include <vector>
#include "Vector.h"

class Moon {
public:
	Moon(const Vector& position);

	bool matches(const Moon& other) const;

	void step();
	void stepComp(int i);
	void addVelocity(const Vector& direction);
	void resetVelocity();

	int energyP() const;
	int enertgyK() const;
	int energyTotal() const;

	const Vector& getPosition() const;

	const Vector& getVelocity() const;

	void print() const;

private:
	Vector position;
	Vector velocity;

};


#endif //DAY12_MOON_H
