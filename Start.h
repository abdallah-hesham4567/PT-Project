#ifndef START_STATEMENT_H
#define START_STATEMENT_H

#include "Statement.h"
#include "ApplicationManager.h"

class Start : public Statement
{
private:
    Connector* pOutConn;
    Point Inlet;
    Point Outlet;
    Point Center;
    Point LCorner;
    virtual void UpdateStatementText();

public:
    Start(Point C);

    

    // connectors helpers
    //Connector* getOutputConnector() const { return pOutConn; }
    //void setOutputConnector(Connector* c) { pOutConn = c; }
    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;
    virtual bool IsPointInside(Point p) const;

    virtual void Draw(Output* pOut) const;
    virtual void Save(ofstream& OutFile) const;
    virtual void Load(ifstream& InFile);
    string getStatementType() const;
    virtual void Edit();
    virtual Statement* Clone() const;

    virtual void SetPosition(Point p) {}
};

#endif