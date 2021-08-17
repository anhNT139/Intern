#include"StateContext.h"

int main() {
	StateContext* context = new StateContext();
	context->open();
	context->unlock();
	context->open();
	context->lock();
	context->close();
	context->lock();
}