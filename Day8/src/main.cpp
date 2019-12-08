#include <iostream>
#include <fstream>
#include "Image.h"

std::unique_ptr<Image> loadImage(std::string path){
	std::ifstream input("../input.txt");
	std::string line;

	input >> line;
	input.close();

	int width = 25, height = 6;
	int pixelsPerLayer = width * height;
	auto image = std::make_unique<Image>(width, height);
	image->createLayer();
	int l = 0;

	for(char c : line){
		int digit = c - 48;

		if(image->getLayer(l).count() == pixelsPerLayer){
			image->createLayer();
			l++;
		}

		image->getLayer(l).pushDigit(digit);
	}

	return image;
}

int main(){
	auto image = loadImage("../input.txt");

	printf("Checksum: %d\n\n", image->checksum());

	image->print();

	return 0;
}