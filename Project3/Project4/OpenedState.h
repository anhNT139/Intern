#pragma once
#include "StateBase.h"

class OpenedState :
    public StateBase
{
public:
    void unlock(StateContext*) override;
    void open(StateContext*) override;
    void close(StateContext*) override;
    void lock(StateContext*) override;
};

