#include "StateContext.h"

void StateContext::setState(StateBase* newState) {
	state = newState;
}

void StateContext::unlock() {
	state->unlock(this);
}

void StateContext::open() {
	state->open(this);
}

void StateContext::close() {
	state->close(this);
}

void StateContext::lock() {
	state->lock(this);
}