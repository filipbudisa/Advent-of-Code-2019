#include <iostream>
#include <vector>
#include <fstream>

struct Line {
	int a;
	int b;
	int offset;
};

struct Wire {
	std::vector<Line> hori;
	std::vector<Line> vert;
	std::vector<bool> picks;
};

struct Move {
	char direction;
	int amount;
};

Move tokenizeMove(std::string move){
	return { move[0], std::atoi(move.substr(1).data()) };
}

std::vector<Move> tokenizeWire(const std::string& line){
	std::vector<Move> moves;

	int last = 0;
	int next = 0;

	while((next = line.find(',', next+1)) != std::string::npos){
		std::string part = line.substr(last, next - last);
		if(part.empty()) continue;

		moves.push_back(tokenizeMove(part));

		last = next+1;
	}

	moves.push_back(tokenizeMove(line.substr(last, line.size() - last)));

	return moves;
}

Wire createWire(const std::vector<Move>& moves){
	std::vector<Line> h, v;
	std::vector<bool> picks;

	std::pair<int, int> pos = { 0, 0 };

	for(Move m : moves){
		if(m.direction == 'U'){
			v.push_back({ pos.second, pos.second + m.amount, pos.first });
			pos.second += m.amount;
			picks.push_back(false);
		}else if(m.direction == 'D'){
			v.push_back({ pos.second, pos.second - m.amount, pos.first });
			pos.second -= m.amount;
			picks.push_back(false);
		}else if(m.direction == 'R'){
			h.push_back({ pos.first, pos.first + m.amount, pos.second });
			pos.first += m.amount;
			picks.push_back(true);
		}else if(m.direction == 'L'){
			h.push_back({ pos.first, pos.first - m.amount, pos.second });
			pos.first -= m.amount;
			picks.push_back(true);
		}
	}

	return { h, v, picks };
}

bool numberWithin(Line line, int number){
	int a, b;
	if(line.a < line.b){
		a = line.a;
		b = line.b;
	}else{
		a = line.b;
		b = line.a;
	}

	return a <= number && number <= b;
}

std::vector<std::pair<int, int>> findCollisions(Wire wireA, Wire wireB){
	std::vector<std::pair<int, int>> collisions;

	for(Line l1 : wireA.hori){
		for(Line l2 : wireB.vert){
			if(numberWithin(l1, l2.offset) && numberWithin(l2, l1.offset)){
				collisions.emplace_back( l2.offset, l1.offset );
			}
		}
	}

	for(Line l1 : wireA.vert){
		for(Line l2 : wireB.hori){
			if(numberWithin(l1, l2.offset) && numberWithin(l2, l1.offset)){
				collisions.emplace_back( l1.offset, l2.offset );
			}
		}
	}

	return collisions;
}

int manhattan(std::pair<int, int> a, std::pair<int, int> b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int wireDistance(Wire wire, std::pair<int, int> point){
	int hi = 0, vi = 0;
	int distance = 0;

	for(bool p : wire.picks){
		Line line = p ? wire.hori[hi++] : wire.vert[vi++];

		if(p && (line.offset == point.second && numberWithin(line, point.first))){
			distance += abs(point.first - line.a);
			return distance;
		}else if(!p && (line.offset == point.first && numberWithin(line, point.second))){
			distance += abs(point.second - line.a);
			return distance;
		}else{
			distance += abs(line.b - line.a);
		}
	}

	return 0;
}

int main(){
	std::vector<Move> movesA, movesB;

	std::ifstream file("../input.txt");
	std::string line;
	file >> line; movesA = tokenizeWire(line);
	file >> line; movesB = tokenizeWire(line);

	Wire wireA = createWire(movesA);
	Wire wireB = createWire(movesB);

	auto collisions = findCollisions(wireA, wireB);

	std::pair<int, int> bestManhattan, bestDistance;
	int bestManhattanVal = 0;
	int bestDistanceVal = 0;

	for(auto c : collisions){
		int m = manhattan({ 0, 0 }, c);
		int d = wireDistance(wireA, c) + wireDistance(wireB, c);

		if(m > 0 && (bestManhattanVal == 0 || m < bestManhattanVal)){
			bestManhattan = c;
			bestManhattanVal = m;
		}

		if(d > 0 && (bestDistanceVal == 0 || d < bestDistanceVal)){
			bestDistance = c;
			bestDistanceVal = d;
		}
	}

	printf("%d, %d\n", bestManhattanVal, bestDistanceVal);

	return 0;
}