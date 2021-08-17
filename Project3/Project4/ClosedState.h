#pragma once
#include "StateBase.h"

class ClosedState :
    public StateBase
{
public:
    void unlock(StateContext*);
    void open(StateContext*);
    void close(StateContext*);
    void lock(StateContext*);
};

