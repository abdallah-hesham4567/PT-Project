#pragma once
#include "Action.h"
#include "WhileStatement.h"
class AddWhile : public Action
{
    Point Position;
    string LHS, RHS, op;
    string ConditionText;

public:
    AddWhile(ApplicationManager* pAppManager);
    virtual void ReadActionParameters();
    virtual void Execute();
    string GetOp() { return op; }
};

