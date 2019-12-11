#ifndef DAY10_POINT_H
#define DAY10_POINT_H


class Point {
public:
	Point(double x, double y);

	double getX() const;

	double getY() const;

private:
	double x, y;
};


#endif //DAY10_POINT_H
