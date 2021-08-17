#include "ClosedState.h"
#include "OpenedState.h"
#include "StateContext.h"
#include <iostream>

void ClosedState::unlock(StateContext* stateContext) {
	std::cout << "Can not unlock, current state is close\n";
}

void ClosedState::open(StateContext* stateContext) {
	stateContext->setState(new OpenedState);
	std::cout << "Changed from closed state to opened state\n";
	delete this;
}

void ClosedState::close(StateContext* stateContext) {
	std::cout << "Can not close, the current state is close\n";
}

void ClosedState::lock(StateContext* stateContext) {
	stateContext->setState(new OpenedState);
	std::cout << "Changed from closed state to locked state\n";
	delete this;
}
