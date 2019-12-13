#ifndef DAY11_ICOMPUTERLISTENER_H
#define DAY11_ICOMPUTERLISTENER_H

class IComputerListener {
public:
	virtual void inputReceived(int data) = 0;
	virtual void noData() = 0;
};

#endif //DAY11_ICOMPUTERLISTENER_H
