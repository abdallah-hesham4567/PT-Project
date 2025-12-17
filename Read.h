#ifndef READ_H
#define READ_H

#include "Statement.h"
#include <string>
#include "ApplicationManager.h"
class Read : public Statement
{
private:
    string VarName;
    Connector* pOutConn;
    Point Inlet;
    Point Outlet;
    Point LeftCorner;
    Point Center;
    virtual void UpdateStatementText();

public:
    Read(Point Lcorner, const std::string& var = "");
    Read();
    void setVarName(const std::string& v);

  
    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;
    virtual bool IsPointInside(Point p) const;

    virtual void Draw(Output* pOut) const;
    virtual void Save(ofstream& OutFile) const;
    virtual void Load(ifstream& InFile);
    string getStatementType() const override { return "READ"; }
    virtual void Edit(Input* pIn, Output* pOut);
    virtual Statement* Clone() const;

    virtual void SetPosition(Point p);
	virtual Point GetPosition() const;
	virtual int GetWidth() const;
	virtual int GetHeight() const;
};

#endif