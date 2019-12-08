#include "Image.h"

Image::Image(unsigned int width, unsigned int height) : width(width), height(height){

}

ImageLayer& Image::createLayer(){
	layers.emplace_back();
	return layers.back();
}

ImageLayer& Image::getLayer(unsigned i){
	return layers[i];
}

unsigned Image::layerCount(){
	return layers.size();
}

std::unique_ptr<ImageLayer> Image::render(){
	auto layer = std::make_unique<ImageLayer>();

	for(int i = 0; i < width * height; i++){
		int digit = 2;

		for(const ImageLayer& layer : layers){
			if(layer.getDigit(i) == 2) continue;

			digit = layer.getDigit(i);
			break;
		}

		layer->pushDigit(digit);
	}

	return layer;
}

void Image::print(){
	auto layer = render();

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int index = i * width + j;
			int digit = layer->getDigit(index);

			if(digit == 0) printf("  ");
			else if(digit == 1) printf("[]");
			else if(digit == 2) printf("  ");
		}
		printf("\n");
	}
}

int Image::checksum(){
	int fewest = 0;
	unsigned fewestCount = layers[0].count(0);

	for(int i = 1; i < layers.size(); i++){
		int count = layers[i].count(0);
		if(count < fewestCount){
			fewest = i;
			fewestCount = count;
		}
	}

	return layers[fewest].count(1) * layers[fewest].count(2);
}
