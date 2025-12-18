#ifndef START_STATEMENT_H
#define START_STATEMENT_H

#include "Statement.h"
#include "ApplicationManager.h"
#include "Variable.h"
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
    
    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;

    virtual bool IsPointInside(Point p) const;

    virtual void Draw(Output* pOut) const;
    virtual void Save(ofstream& OutFile) const;
    virtual void Load(ifstream& InFile);
    string getStatementType() const {
        return "STRT";
    }

    virtual void Edit(Input* pIn, Output* pOut);
    virtual Statement* Clone() const;

    virtual void SetPosition(Point p);
	virtual Point GetPosition() const;
	virtual int GetWidth() const;
	virtual int GetHeight() const;

    virtual void Execute(Variable vars[], int& varCount, Input* pIn, Output* pOut) {} // we donot need it but it is pure virtual
};

#endif