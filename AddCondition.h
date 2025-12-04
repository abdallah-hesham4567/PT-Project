#pragma once
#include "Action.h"
#include "ConditionStatement.h"

class AddCondition : public Action
{
    
    Point Position;
	string LHS;    //Left Hand Side of the assignment
    string RHS;
	string op;	 //operator of the assignment
	string ConditionText;


public:
    AddCondition(ApplicationManager* pAppManager);
    virtual void ReadActionParameters();
    virtual void Execute();
};
