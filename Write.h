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
};

#endif