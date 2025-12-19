#ifndef WRITE_H
#define WRITE_H
#include "Statement.h"
#include <string>
using namespace std;

class Write : public Statement
{
private:
    string Expr;
    Connector* pOutConn;
    Point Inlet;
    Point Outlet;
    Point LeftCorner;
    Point Center;
    

public:
    Write(Point Lcorner, const string& expr = "");
   
    void setExpr(const string& e);

    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;
    virtual string getStatementType() const { return "WRITE"; }
    

    virtual void Draw(Output* pOut) const;
    virtual void Save(ofstream& OutFile) const ;
    virtual void Load(ifstream& InFile);
	virtual void Edit(Input* pIn, Output* pOut);
    virtual Statement* Clone() const;


    virtual void SetPosition(Point p);
	virtual Point GetPosition() const;
	virtual int GetWidth() const;
	virtual int GetHeight() const;
    virtual bool IsPointInside(Point p) const;

    virtual void UpdateStatementText();
	virtual void Execute(Variable vars[], int& varCount, Input* pIn, Output* pOut);
    string GetVariableName() const { return Expr; }

};

#endif