#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <algorithm>
#include "Point.h"
#include "Line.h"

#include "bitmap.hpp"

std::vector<Point> loadData(const std::string& path){
	std::vector<Point> points;

	std::ifstream input(path);
	std::string line;

	int i = 0;
	while(input >> line){
		for(int j = 0; j < line.length(); j++){
			if(line[j] == '\0' || line[j] == '\n') break;
			if(line[j] == '#') points.emplace_back(j, i);
		}

		i++;
	}

	return points;
}

std::vector<unsigned> calcViews(const std::vector<Point>& asteroids){
	std::vector<unsigned> views;

	for(int i = 0; i < asteroids.size(); i++){
		unsigned astViews = 0;
		std::vector<unsigned> skip;

		for(int j = 0; j < asteroids.size(); j++){
			if(i == j) continue;

			bool doSkip = false;
			for(unsigned s : skip){
				if(s == j){
					doSkip = true;
					break;
				}
			}
			if(doSkip) continue;

			Line line(asteroids[i], asteroids[j]);

			std::vector<unsigned> onLine;

			for(int k = 0; k < asteroids.size(); k++){
				if(k == i) continue;
				if(line.onLine(asteroids[k])) onLine.push_back(k);
			}

			if(onLine.size() == 1){
				astViews++;
				continue;
			}

			double astProgress = line.lineProgress(asteroids[i]);
			bool a = false, b = false;

			for(unsigned pi : onLine){
				Point p = asteroids[pi];
				skip.push_back(pi);
				if(line.lineProgress(p) < astProgress) a = true;
				else b = true;
			}

			if(a) astViews++;
			if(b) astViews++;
		}

		views.push_back(astViews);
	}

	return views;
}

template <typename  T> bool contains(std::vector<T> collection, T item){
	for(T t : collection){
		if(t == item) return true;
	}

	return false;
}

double distance(Point a, Point b){
	return pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2);
}

int main(){
	std::vector<Point> asteroids = loadData("../input.txt");

	std::vector<unsigned> views = calcViews(asteroids);

	unsigned best = 0;
	for(int i = 1; i < asteroids.size(); i++){
		if(views[i] > views[best]) best = i;
	}

	printf("Best: %d\n", views[best]);

	Point station = asteroids[best];

	std::vector<std::pair<double, unsigned>> asteroidAngles;

	for(int i = 0; i < asteroids.size(); i++){
		if(i == best) continue;
		Point p = asteroids[i];
		double angle = atan2(p.getY() - station.getY(), p.getX() - station.getX());
		if(angle < -M_PI_2) angle += M_PI * 2.0;
		asteroidAngles.emplace_back(angle, i);
	}

	std::sort(asteroidAngles.begin(), asteroidAngles.end());

	bitmap_image img(24, 24);
	img.set_all_channels(0, 0, 0);

	for(Point p : asteroids){
		img.set_pixel(p.getX(), p.getY(), 200, 0, 0);
	}

	img.set_pixel(station.getX(), station.getY(), 0, 200, 0);

	img.save_image("../images/000.bmp");
	int pixel = 1;
	std::string filename; filename.resize(30);

	std::vector<unsigned> blasted;
	while(blasted.size() != asteroids.size()-1){
		for(unsigned i = 0; i < asteroidAngles.size(); i++){
			if(contains(blasted, asteroidAngles[i].second)) continue;

			std::vector<unsigned> sameAngle;
			for(unsigned j = i; j < asteroidAngles.size(); j++){
				if(fabs(fabs(asteroidAngles[i].first - asteroidAngles[j].first)) < 1e-6){
					sameAngle.push_back(asteroidAngles[j].second);
				}else{
					break;
				}
			}

			unsigned closest;
			double closestDist = -1;

			for(int j = 0; j < sameAngle.size(); j++){
				if(contains(blasted, sameAngle[j])){
					continue;
				}

				double dist = distance(station, asteroids[sameAngle[j]]);
				if(closestDist == -1 || dist < closestDist){
					closest = sameAngle[j];
					closestDist = dist;
				}
			}

			if(closestDist == -1) continue;

			blasted.push_back(closest);
			Point p = asteroids[closest];
			if(blasted.size() == 200){
				img.set_pixel(p.getX(), p.getY(), 150, 250, 0);
			}else{
				img.set_pixel(p.getX(), p.getY(), 50, 50, 50);
			}
			sprintf(filename.data(), "../images/%03d.bmp", pixel++);
			img.save_image(filename);

			//if(blasted.size() == 200) break;

			i += sameAngle.size() - 1;
		}
	}

	Point last = asteroids[blasted[199]];

	printf("200.: [ %d, %d ] / %d\n", (int) last.getX(), (int) last.getY(), (int) (last.getX()*100.0 + last.getY()));

	return 0;
}