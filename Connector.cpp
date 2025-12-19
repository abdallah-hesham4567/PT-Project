#include "Connector.h"
#include "Statement.h"
#include "GUI/Output.h"
#include <cmath>
Connector::Connector(Statement* Src, Statement* Dst, int outletBranch)
{
	SrcStat = Src;
	DstStat = Dst;
	Selected = false;
	OutletBranch = outletBranch;

	UpdateConnectionPoints();
}

void Connector::setSrcStat(Statement* Src)
{
	SrcStat = Src;
	UpdateConnectionPoints();
}

Statement* Connector::getSrcStat()
{
	return SrcStat;
}

void Connector::setDstStat(Statement* Dst)
{
	DstStat = Dst;
	UpdateConnectionPoints();
}

Statement* Connector::getDstStat()
{
	return DstStat;
}


void Connector::setStartPoint(Point P)
{
	Start = P;
}

Point Connector::getStartPoint()
{
	return Start;
}

void Connector::setEndPoint(Point P)
{
	End = P;
}

Point Connector::getEndPoint()
{
	return End;
}


void Connector::setOutletBranch(int branch)
{
	OutletBranch = branch;
}

int Connector::getOutletBranch() const
{
	return OutletBranch;
}

void Connector::SetSelected(bool s)
{
	Selected = s;
}

bool Connector::IsSelected() const
{
	return Selected;
}

void Connector::UpdateConnectionPoints()                
{
	if (SrcStat && DstStat) 
	{
		// Get the outlet point from source statement
		Start = SrcStat->GetOutletPoint(OutletBranch);

		// Check if source is a Condition or While
		if (DstStat->IsConditional())                 // to check draw a connector up or down in case condition
		{
			Point p1 = DstStat->GetInletPoint();
			Point p2 = SrcStat->GetOutletPoint();
			// If destination is below source → inlet goes to top of destination
			if (p2.y>p1.y)
			{
				End = DstStat->GetInletPoint();
				End.y += UI.COND_HI;
			}
			else // If destination is above or overlapping → inlet goes to bottom
			{
				End = DstStat->GetInletPoint() ;
				
			}
		}
		else
		{
			// For other statements → default inlet
			End = DstStat->GetInletPoint();
		}
	}
}

void Connector::Draw(Output* pOut) const
{
	// Draw connector line from source to destination
	// The connector should be drawn highlighted if selected
	if (pOut)
	{
		// Calculate midpoint for L-shaped connector
		Point midPoint;
		midPoint.x = End.x;      // Move horizontally to destination's x
		midPoint.y = Start.y;    // Keep source's y

		// Draw two line segments instead of one
		// Segment 1: Start → MidPoint (horizontal)
		pOut->DrawMidPoint(Start, midPoint, Selected);

		// Segment 2: MidPoint → End (vertical)
		pOut->DrawConnector(midPoint, End, Selected);
	}
}

bool Connector::IsPointInConnector(Point p) const  
{
	const int TOLERANCE = 5; // pixels

	// For L-shaped connector with midpoint
	Point midPoint;
	midPoint.x = End.x;
	midPoint.y = Start.y;

	// Check if point is near first segment (Start → Mid)
	bool nearSegment1 = IsPointNearSegment(p, Start, midPoint, TOLERANCE);

	// Check if point is near second segment (Mid → End)
	bool nearSegment2 = IsPointNearSegment(p, midPoint, End, TOLERANCE);

	return nearSegment1 || nearSegment2;
}

void Connector::Save(ofstream& OutFile) const
{
	// Save connector information to file
	// Format: Source_Statement_ID Target_Statement_ID Outlet_branch
	
		OutFile << SrcStat->GetID() << " "
			<< DstStat->GetID() << " "
			<< OutletBranch << endl;
	
}

void Connector::Load(ifstream& InFile)
{
	
	InFile >> OutletBranch;
	
}


bool Connector::Validate(string& errorMsg) const
{
	// Validate that the connector has valid source and destination
	if (!SrcStat)
	{
		errorMsg = "Connector has no source statement";
		return false;
	}

	if (!DstStat)
	{
		errorMsg = "Connector has no destination statement";
		return false;
	}

	// Check that source and destination are different
	if (SrcStat == DstStat)
	{
		errorMsg = "Connector source and destination cannot be the same";
		return false;
	}

	// Additional validation can be added here
	// For example, checking if the outlet branch is valid for the source statement type

	return true;
}

bool Connector::IsPointNearSegment(Point p, Point segStart, Point segEnd, int tolerance) const
{
	double dx = segEnd.x - segStart.x;
	double dy = segEnd.y - segStart.y;

	if (dx == 0 && dy == 0)
	{
		double dist = sqrt(pow(p.x - segStart.x, 2) + pow(p.y - segStart.y, 2));
		return dist <= tolerance;
	}

	double t = ((p.x - segStart.x) * dx + (p.y - segStart.y) * dy) / (dx * dx + dy * dy);

	if (t < 0) t = 0;
	if (t > 1) t = 1;

	double closestX = segStart.x + t * dx;
	double closestY = segStart.y + t * dy;

	double distance = sqrt(pow(p.x - closestX, 2) + pow(p.y - closestY, 2));

	return distance <= tolerance;
}












Connector::~Connector()
{
	// Destructor
	// Note: We don't delete SrcStat or DstStat here because they are managed elsewhere
	// The connector only maintains pointers to them
}

