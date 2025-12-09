#ifndef WRITE_H
#define WRITE_H

#include "Statement.h"
#include <string>

class Write : public Statement
{
private:
    std::string Expr;

    Connector* pOutConn;
    Point Inlet;
    Point Outlet;
    Point LeftCorner;

    virtual void UpdateStatementText();

public:
    Write(Point Lcorner, const std::string& expr = "");

    void setExpr(const std::string& e);

    virtual void Draw(Output* pOut) const;

    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;
    virtual bool IsPointInside(Point p) const;

    virtual void Draw(Output* pOut) const;
    virtual void Save(ofstream& OutFile) const;
    virtual void Load(ifstream& InFile);
};

#endif