#pragma once
#include "LockedState.h"

class StateContext
{
private:
	StateBase *state;
public:
	StateContext() {
		state = new LockedState();
	}
	void setState(StateBase*);
	void unlock();
	void open();
	void close();
	void lock();
};

