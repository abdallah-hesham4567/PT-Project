#pragma once
#include "Action.h"
class ActionLoad : public Action
{
private:
    string FileName; // Name of the file to load from

public:
    ActionLoad(ApplicationManager* pAppManager);

    // Reads the filename from the user
    virtual void ReadActionParameters();

    // Executes the load action
    virtual void Execute();

};

