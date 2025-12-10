#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"

class ActionSelect : public Action
{
public:
    ActionSelect(ApplicationManager* pAppManager);
    virtual void ReadActionParameters() override {}
    virtual void Execute();
};
