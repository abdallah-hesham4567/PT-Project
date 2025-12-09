#ifndef END_STATEMENT_H
#define END_STATEMENT_H

#include "Statement.h"

class End : public Statement
{
private:
    Connector* pInConn;
    Point Inlet;
    Point Outlet;
    Point Center;

    virtual void UpdateStatementText();

public:
    End(Point C);

    virtual void Draw(Output* pOut) const;

    Connector* getInputConnector() const { return pInConn; }
    void setInputConnector(Connector* c) { pInConn = c; }
};

#endif