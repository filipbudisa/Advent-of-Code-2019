#include <cmath>
#include "Line.h"

Line::Line(Point first, Point second){
	double xDiff = second.getX() - first.getX();

	if(fabs(xDiff) < 1e-6){
		vertical = true;
		b = first.getX();
	}else{
		a = (second.getY() - first.getY()) / (xDiff);
		b = first.getY() - a * first.getX();
	}
}

bool Line::onLine(Point point){
	if(vertical){
		return fabs(point.getX() - b) < 1e-6;
	}else{
		return fabs(a * point.getX() + b - point.getY()) < 1e-6;
	}
}

double Line::lineProgress(Point point){
	if(vertical){
		return point.getY();
	}else if(fabs(a) < 1e-6){
		return point.getX();
	}else{
		return a * point.getX() + b;
	}
}
