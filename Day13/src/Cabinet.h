#ifndef DAY13_CABINET_H
#define DAY13_CABINET_H

#include <array>
#import "IComputerListener.h"
#import "Computer.h"
#include "Joystick.h"

class Cabinet : public IComputerListener {
public:

	enum TileId {
		EMPTY, WALL, BLOCK, PADDLE, BALL
	};

	Cabinet(Computer& computer);

	void inputReceived(int data) override;

	void noData() override;

	void draw();

	unsigned count(TileId tile);

	int getScore() const;

	void reset();

private:

	std::array<std::string, 5> print = {
			"   ", "[_]", "[x]", "===", "(0)"
	};

	std::array<std::string, 3> pointer = { "<---o", "    o    ", "    o--->" };

	void processSequence();

	Computer& computer;

	std::vector<int> sequence;

	std::vector<std::vector<TileId>> grid;

	int score = 0;
};


#endif //DAY13_CABINET_H
