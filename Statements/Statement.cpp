#include "Statement.h"
int Statement::NextID = 1;  // initialize static member
Statement::Statement()
{
	//TODO: set the ID with a unique value
	ID = NextID++;   // assign unique ID
	Text = "";
	Selected = false;
}

void Statement::SetSelected(bool s)
{
	Selected = s;
}

bool Statement::IsSelected() const
{
	return Selected;
}

void Statement::GetExpectedOutConnCount(Connector* pConn)
{

}