#include "Select.h"

Select::Select(Statement* pS)
{
    pStat = pS;
    Selected = false;
}

void Select::SetStatement(Statement* pS)
{
    pStat = pS;
}

void Select::SetSelected(bool s)
{
    Selected = s;
}

void Select::Toggle()
{
    Selected = !Selected;
}

bool Select::IsSelected() const
{
    return Selected;
}

Statement* Select::GetStatement() const
{
    return pStat;
}

bool Select::ClickedInside(Point P) const
{
    if (!pStat)
        return false;

    // Here we use the statement's IsPointInside()
    return pStat->IsPointInside(P);
}
