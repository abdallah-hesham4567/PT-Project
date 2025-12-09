#ifndef START_STATEMENT_H
#define START_STATEMENT_H

#include "Statement.h"

class Start : public Statement
{
private:
    Connector* pOutConn;
    Point Inlet;
    Point Outlet;
    Point Center;

    virtual void UpdateStatementText();

public:
    Start(Point C);

    virtual void Draw(Output* pOut) const;

    // connectors helpers
    Connector* getOutputConnector() const { return pOutConn; }
    void setOutputConnector(Connector* c) { pOutConn = c; }
};

#endif