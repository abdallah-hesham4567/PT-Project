#include "Statement.h"
int Statement::NextID = 1;  // initialize static member
Statement::Statement()
{
	//TODO: set the ID with a unique value
	ID = NextID++;   // assign unique ID
	Text = "";
	Selected = false;
	pOutconn = NULL;
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

Connector* Statement::GetOutConn()
{
	return pOutconn;
}
void Statement::AddIncomingConnector(Connector* pConn)
{

}
void Statement::RemoveIncomingConnector(Connector* pConn)
{

}
int Statement::GetIncomingCount()
{
	
}
Connector* Statement::GetIncomingConnector(int index)
{
	return nullptr;
}


void Statement::SetOutConnector(Connector* pConn)
{
	pOutconn = pConn;
}



