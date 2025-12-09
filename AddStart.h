#ifndef ADD_START_H
#define ADD_START_H

#include "Action.h"
#include "Start.h"

class AddStart : public Action
{
private:
    Point Position;

public:
    AddStart(ApplicationManager* pAppManager);

    virtual void ReadActionParameters();
    virtual void Execute();
};

#endif