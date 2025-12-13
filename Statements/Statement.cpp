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

bool Statement::IsOverlapping(Point p, int w, int h) const
{
	// Check for overlap between this statement and the rectangle defined by (p, w, h)
	Point thisPos = GetPosition();
	int thisW = GetWidth();
	int thisH = GetHeight();
	// Check if rectangles overlap
	if (thisPos.x < p.x + w &&
		thisPos.x + thisW > p.x &&
		thisPos.y < p.y + h &&
		thisPos.y + thisH > p.y)
	{
		return true; // Overlapping
	}
	return false; // Not overlapping
}






