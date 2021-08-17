#include "LockedState.h"
#include "ClosedState.h"
#include "StateContext.h"
#include <iostream>


void LockedState::unlock(StateContext* stateContext) {
	stateContext->setState(new ClosedState);
	std::cout << "Changed from locked state to closed state\n";
	delete this;
}

void LockedState::open(StateContext* stateContext) {
	std::cout << "Need unlock first\n";
}

void LockedState::close(StateContext* stateContext) {
	std::cout << "Can not close, the current state is lock\n";
}

void LockedState::lock(StateContext* stateContext) {
	std::cout << "Can not lock, the current state is lock\n";
}
