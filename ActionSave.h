#pragma once
#include "Action.h"
class ActionSave :public Action
{
private:
    string FileName; // Name of the file to save to

public:
    ActionSave(ApplicationManager* pAppManager);

    // Reads the filename from the user
    virtual void ReadActionParameters();

    // Executes the save action
    virtual void Execute();
};


