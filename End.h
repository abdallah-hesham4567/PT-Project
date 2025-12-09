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
    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;
    virtual bool IsPointInside(Point p) const;
    virtual void Save(ofstream& OutFile) const;
    virtual void Load(ifstream& InFile);
    string getStatementType() const;
    virtual void Edit(ApplicationManager* pManager);
    virtual Statement* Clone() const;

};

#endif