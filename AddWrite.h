#ifndef ADD_WRITE_H
#define ADD_WRITE_H

#include "Action.h"
#include "..\Statements\Write.h"

class AddWrite : public Action
{
private:
    Point Position;
    std::string Expr;

public:
    AddWrite(ApplicationManager* pAppManager);

    virtual void ReadActionParameters();
    virtual void Execute();
};

#endif