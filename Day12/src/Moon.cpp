#include <cstdio>
#include "Moon.h"

Moon::Moon(const Vector& position) : position(position), velocity({ 0, 0, 0 }){}

int Moon::energyP() const{
	return position.sumAbs();
}

int Moon::enertgyK() const{
	return velocity.sumAbs();
}

int Moon::energyTotal() const{
	return energyP() * enertgyK();
}

void Moon::step(){
	position += velocity;
}

void Moon::stepComp(int i){
	position[i] += velocity[i];
}

void Moon::addVelocity(const Vector& direction){
	velocity += direction;
}

void Moon::resetVelocity(){
	velocity = { 0, 0, 0 };
}

const Vector& Moon::getPosition() const{
	return position;
}

void Moon::print() const{
	printf("s = [ %d %d %d ], v = [ %d %d %d ]\n", position[0], position[1], position[2], velocity[0], velocity[1], velocity[2]);
}

bool Moon::matches(const Moon& other) const{
	if(position.size() != other.position.size()) return false;

	for(int i = 0; i < position.size(); i++){
		if(position[i] != other.position[i]){
			return false;
		}
	}

	return true;
}

const Vector& Moon::getVelocity() const{
	return velocity;
}
