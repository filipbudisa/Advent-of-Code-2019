#include <cstdio>
#include <unistd.h>
#include "Cabinet.h"

Cabinet::Cabinet(Computer& computer) : computer(computer){

}

void Cabinet::inputReceived(int data){
	sequence.push_back(data);

	if(sequence.size() == 3){
		processSequence();
		sequence.clear();
	}
}

void Cabinet::noData(){
	int bPos, pPos;
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			if(grid[i][j] == PADDLE){
				pPos = j;
			}
			if(grid[i][j] == BALL){
				bPos = j;
			}
		}
	}

	std::vector<long> data;

	int state = pPos - bPos;
	if(state < 0){
		data.push_back(1);
	}else if(state > 0){
		data.push_back(-1);
	}else{
		data.push_back(0);
	}

	computer.setInput(data);
}

void Cabinet::processSequence(){
	int col = sequence[0];
	int row = sequence[1];
	int val = sequence[2];

	if(col == -1){
		score = val;
		return;
	}

	TileId id = TileId(val);

	if(grid.size() <= row){
		grid.resize(row + 1);
	}

	if(grid[row].size() <= col){
		grid[row].resize(col + 1);
	}

	grid[row][col] = id;
}

void Cabinet::draw(){
	for(const std::vector<TileId>& row : grid){
		for(TileId tile : row){
			printf("%s", print[tile].data());
		}
		printf("\n");
	}

	printf("Score: %d\n", score);
}

unsigned Cabinet::count(Cabinet::TileId tile){
	unsigned count = 0;

	for(const std::vector<TileId>& row : grid){
		for(TileId t : row){
			count += tile == t;
		}
	}

	return count;
}

void Cabinet::reset(){
	sequence.clear();
	grid.clear();
	score = 0;
}

int Cabinet::getScore() const{
	return score;
}
