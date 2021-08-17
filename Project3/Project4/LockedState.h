#pragma once
#include "StateBase.h"

class LockedState :
    public StateBase
{
public:
    void unlock(StateContext*);
    void open(StateContext*);
    void close(StateContext*);
    void lock(StateContext*);
};

