#include "OpenedState.h"
#include "ClosedState.h"
#include "StateContext.h"
#include <iostream>

void OpenedState::unlock(StateContext* stateContext) {
	std::cout << "Can not unlock, current state is open\n";
}

void OpenedState::open(StateContext* stateContext) {
	std::cout << "Can not open, current state is open\n";
}

void OpenedState::close(StateContext* stateContext) {
	stateContext->setState(new ClosedState);
	std::cout << "Changed from opened state to closed state\n";
	delete this;
}

void OpenedState::lock(StateContext* stateContext) {
	std::cout << "Can not lock, current state is open\n";
}
