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

    void setVarName(const std::string& v);

    virtual void Draw(Output* pOut) const;
    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;
    virtual bool IsPointInside(Point p) const;

    virtual void Draw(Output* pOut) const;
    virtual void Save(ofstream& OutFile) const;
    virtual void Load(ifstream& InFile);
    string getStatementType() const override { return "READ"; }
    virtual void Edit(ApplicationManager* pManager);
    virtual Statement* Clone() const;
};

#endif