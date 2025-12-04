#pragma once
#include "Action.h"
#include "..\Defs.h"
#include <string>
#include <sstream>
#include "DeclareStatement.h"
using namespace std;

class AddDeclare : public Action
{
    Point Position;
    string VariableName;
    double Value;
    bool HasValue;

public:
    AddDeclare(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
};
