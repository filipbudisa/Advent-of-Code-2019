#include <cmath>
#include "Robot.h"

Robot::Robot(Computer& computer) : computer(computer){

	computer.registerListener(this);
}

void Robot::inputReceived(int data){
	if(state == 0){
		inputPaint(data);
		state = 1;
	}else{
		inputRot(data);
		state = 0;
	}
}

void Robot::inputPaint(int color){
	paint(color);

	hullWasPainted.insert(location);
}

void Robot::inputRot(int direction){
	if(direction == 1){
		rotation--;
	}else{
		rotation++;
	}

	auto rot = std::make_pair((int) round(sin(M_PI_2 * rotation)), (int) round(cos(M_PI_2 * rotation)));
	location = location + rot;
}

void Robot::noData(){
	std::vector<long> data = { static_cast<long>(hullWhite.count(location)) };
	computer.setInput(data);
	computer.run();
}

unsigned Robot::hullPainted(){
	return hullWasPainted.size();
}

void Robot::paint(int color){
	if(color == 1){
		hullWhite.insert(location);
	}else{
		hullWhite.erase(location);
	}
}

void Robot::reset(){
	hullWhite.clear();
	hullWasPainted.clear();
	rotation = 1;
	location = { 0, 0 };
	state = 0;
}

void Robot::print(){
	printCollection(hullWhite);
}

void Robot::printPainted(){
	printCollection(hullWasPainted);
}

void Robot::printCollection(std::set<std::pair<int, int>>& collection){
	int xmin = collection.begin()->first, ymin = collection.begin()->second;
	int xmax = collection.begin()->first, ymax = collection.begin()->second;

	for(auto p : collection){
		if(p.first < xmin) xmin = p.first;
		if(p.second < ymin) ymin = p.second;
		if(p.first > xmax) xmax = p.first;
		if(p.second > ymax) ymax = p.second;
	}

	for(int i = xmax+1; i >= xmin-1; i--){
		for(int j = ymin-1; j <= ymax; j++){
			if(collection.count(std::make_pair(i, j))){
				printf("##");
			}else{
				printf("  ");
			}
		}

		printf("\n");
	}
}
