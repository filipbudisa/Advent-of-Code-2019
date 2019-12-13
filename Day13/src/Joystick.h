#ifndef DAY13_JOYSTICK_H
#define DAY13_JOYSTICK_H

#include <termios.h>

/**
 * Keyboard control for the cabinet. Initialize in cabinet, call update() to update input, and getKey() for -1 0 or 1
 */
class Joystick {
public:
	Joystick();

	void update();

	short getKey();

private:
	void captureKeyboard();
	void releaseKeyboard();

	void processKey();

	termios term = {  };

	bool rDown = false;
	bool lDown = false;
};


#endif //DAY13_JOYSTICK_H
