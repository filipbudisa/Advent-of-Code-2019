#ifndef DAY11_ROBOT_H
#define DAY11_ROBOT_H


#include <set>
#include "Computer.h"


// courtesy of stackoverflow
template<typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r){
	return {l.first + r.first, l.second + r.second};
}

class Robot : public IComputerListener {
public:

	Robot(Computer& computer);

	unsigned hullPainted();

	void paint(int color);

	void reset();

	void print();
	void printPainted();

	void inputReceived(int data) override;
	void noData() override;

private:
	Computer& computer;
	std::set<std::pair<int, int>> hullWhite;

	void inputPaint(int color);
	void inputRot(int direction);

	std::pair<int, int> location = { 0, 0 };
	double rotation = 1;

	std::set<std::pair<int, int>> hullWasPainted;

	short state = 0; // 0 - awaiting first bit, 1 - awaiting second bit

	void printCollection(std::set<std::pair<int, int>>& collection);
};


#endif //DAY11_ROBOT_H
