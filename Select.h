#pragma once

#include "Statement.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

// A helper class to manage selection state of statements
class Select
{
private:
    Statement* pStat;   // pointer to the statement we want to control
    bool Selected;

public:
    Select(Statement* pS = nullptr);

    // Setters
    void SetStatement(Statement* pS);
    void SetSelected(bool s);
    void Toggle();

    // Getters
    bool IsSelected() const;
    Statement* GetStatement() const;

    // Interaction
    // (Call this after a click event)
    bool ClickedInside(Point P) const;
};
