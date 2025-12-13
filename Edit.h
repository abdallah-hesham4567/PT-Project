#ifndef EDIT_H
#define EDIT_H

#include "Action.h"

class Edit : public Action
{
public:
    Edit(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
};

#endif
