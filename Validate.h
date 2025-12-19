#pragma once
#include "Action.h"
#include "ApplicationManager.h"
class Validate : public Action
{
public:
    Validate(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
};

