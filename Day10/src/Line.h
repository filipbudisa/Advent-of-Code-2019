#ifndef DAY10_LINE_H
#define DAY10_LINE_H


#include "Point.h"

class Line {
public:
	Line(Point first, Point second);

	bool onLine(Point point);

	double lineProgress(Point point);

private:
	double a, b;
	bool vertical = false;
};


#endif //DAY10_LINE_H
