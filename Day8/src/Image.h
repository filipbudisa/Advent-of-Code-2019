#ifndef DAY8_IMAGE_H
#define DAY8_IMAGE_H


#include <vector>
#include <memory>
#include "ImageLayer.h"

class Image {
public:
	Image(unsigned int width, unsigned int height);

	ImageLayer& createLayer();
	ImageLayer& getLayer(unsigned i);
	unsigned layerCount();
	int checksum();
	void print();

private:
	std::unique_ptr<ImageLayer> render();

	unsigned width;
	unsigned height;
	std::vector<ImageLayer> layers;
};


#endif //DAY8_IMAGE_H
