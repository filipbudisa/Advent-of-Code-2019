#ifndef DAY8_IMAGELAYER_H
#define DAY8_IMAGELAYER_H


#include <vector>

class ImageLayer {
public:
	ImageLayer();

	void pushDigit(int digit);
	int getDigit(unsigned i) const;

	unsigned count(int digit);
	unsigned count();

private:
	std::vector<int> data;
};


#endif //DAY8_IMAGELAYER_H
