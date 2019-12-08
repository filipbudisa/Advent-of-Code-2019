#include "ImageLayer.h"

ImageLayer::ImageLayer(){

}

unsigned ImageLayer::count(int digit){
	int c  = 0;

	for(int d : data){
		if(d == digit) c++;
	}

	return c;
}

void ImageLayer::pushDigit(int digit){
	data.push_back(digit);
}

unsigned ImageLayer::count(){
	data.size();
}

int ImageLayer::getDigit(unsigned i) const {
	return data[i];
}

