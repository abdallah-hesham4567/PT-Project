#ifndef PASTE_H
#define PASTE_H

#include "Action.h"

class Paste : public Action
{
public:
    Paste(ApplicationManager* pApp);

    virtual void ReadActionParameters() override {}
    virtual void Execute();
};

#endif
