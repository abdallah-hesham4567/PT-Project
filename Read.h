#ifndef READ_H
#define READ_H

#include "Statement.h"
#include <string>

class Read : public Statement
{
private:
    std::string VarName;
    Connector* pOutConn;
    Point Inlet;
    Point Outlet;
    Point LeftCorner;

    virtual void UpdateStatementText();

public:
    Read(Point Lcorner, const std::string& var = "");

    void setVarName(const std::string& v);

    virtual void Draw(Output* pOut) const;
};

#endif