#ifndef EDIT_H
#define EDIT_H

#include "Action.h"
#include "Statement.h"

class Edit : public Action
{
private:
    Statement* SelectedStat;
    // The selected statement to edit
public:
    Edit(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
};

#endif
