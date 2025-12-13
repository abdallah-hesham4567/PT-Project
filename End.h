#ifndef END_STATEMENT_H
#define END_STATEMENT_H

#include "Statement.h"
#include "ApplicationManager.h"
class End : public Statement
{
private:
    Connector* pInConn;
    Point Inlet;
    Point Outlet;
    Point Center;
    Point LCorner;
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
    string getStatementType() const { return "END"; }
    virtual void Edit(Input* pIn, Output* pOut );
    virtual Statement* Clone() const;

    virtual void SetPosition(Point p) {}
	virtual Point GetPosition() const;
	virtual int GetWidth() const;
	virtual int GetHeight() const;

};

#endif