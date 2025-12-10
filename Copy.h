#ifndef COPY_H
#define COPY_H

#include "Action.h"
#include "../Statements/Statement.h"
class Copy : public Action
{
public:
    virtual void ReadActionParameters() override {}
    Copy(ApplicationManager* pApp);
    bool CopyToClipboard(Statement* pStat);
    virtual void Execute();
};

#endif
