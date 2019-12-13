#include <cstdio>
#include <unistd.h>
#include <poll.h>
#include "Joystick.h"

Joystick::Joystick(){
	captureKeyboard();
}

short Joystick::getKey(){
	if(lDown == rDown) return 0;
	if(lDown) return -1;
	if(rDown) return +1;

	return 0;
}

void Joystick::captureKeyboard(){
	// define a terminal configuration data structure

	// copy the stdin terminal configuration into term
	tcgetattr(fileno(stdin), &term);

	// turn off Canonical processing in term
	term.c_lflag &= ~ICANON;

	// turn off screen echo in term
	term.c_lflag &= ~ECHO;

	// set the terminal configuration for stdin according to term, now
	tcsetattr(fileno(stdin), TCSANOW, &term);

}

void Joystick::releaseKeyboard(){
	// turn on Canonical processing in term
	term.c_lflag |= ICANON;

	// turn on screen echo in term
	term.c_lflag |= ECHO;

	// set the terminal configuration for stdin according to term, now
	tcsetattr(fileno(stdin), TCSANOW, &term);
}

void Joystick::update(){
	pollfd set = { 0, POLLIN, 0 };
	timespec timeout = { 0, 0 };
	int data = ppoll(&set, 1, &timeout, nullptr);

	while(data > 0 && set.revents & POLLIN){
		processKey();

		set = { 0, POLLIN, 0 };
		timeout = { 0, 0 };
		data = ppoll(&set, 1, &timeout, nullptr);
	}
}

void Joystick::processKey(){
	char c;

	read(0, &c, 1);

	if(c == 27){
		read(0, &c, 1);

		if(c == 91){
			read(0, &c, 1);

			switch(c){
				case 68:
					rDown = false;
					lDown = true;
					break;
				case 67:
					lDown = false;
					rDown = true;
					break;
				case 66:
					lDown = rDown = false;
					break;
			}

			printf("L %d, D %d\n", lDown, rDown);
		}
	}
}
