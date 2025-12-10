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

 void Statement::SetOutConn(Connector* pConn)
{
	pOutconn = pConn;
}

Connector* Statement::GetOutConn()
{
	return pOutconn;
}

int Statement::GetIncomingCount()
{
	return 1;
}
Connector* Statement::GetIncomingConnector(int index)
{
	return nullptr;
}





