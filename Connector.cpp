//#include "Connector.h"
//
//Connector::Connector(Statement* Src, Statement* Dst)	
////When a connector is created, it must have a source statement and a destination statement
////There are NO FREE connectors in the flowchart
//{
//	
//	SrcStat = Src;
//	DstStat = Dst;
//}
//
//void Connector::setSrcStat(Statement *Src)
//{	SrcStat = Src;	}
//
//Statement* Connector::getSrcStat()
//{	return SrcStat;	}
//
//void Connector::setDstStat(Statement *Dst)
//{	DstStat = Dst;	}
//
//Statement* Connector::getDstStat()
//{	return DstStat;	}
//
//
//void Connector::setStartPoint(Point P)
//{	Start = P;	}
//
//Point Connector::getStartPoint()
//{	return Start;	}
//
//void Connector::setEndPoint(Point P)
//{	End = P;	}
//
//Point Connector::getEndPoint()
//{	return End;	}
//
//void Connector::Draw(Output* pOut) const
//{
//	///TODO: Call Output to draw a connector from SrcStat to DstStat on the output window
//}


//// ==================== Connector.h ====================
//#ifndef CONNECTOR_H
//#define CONNECTOR_H
//
//#include "Defs.h"
//#include <fstream>
//
//class Statement; // Forward declaration
//class Output;    // Forward declaration
//
//class Connector
//{
//private:
//	Statement* SrcStat;  // Pointer to source statement
//	Statement* DstStat;  // Pointer to destination statement
//	Point Start;         // Start point of the connector (outlet of source)
//	Point End;           // End point of the connector (inlet of destination)
//	bool Selected;       // True if connector is selected
//	int OutletBranch;    // 0 for normal, 1 for YES branch, 2 for NO branch (for conditional statements)
//
//public:
//	// Constructor: creates a connector between two statements
//	Connector(Statement* Src, Statement* Dst, int outletBranch = 0);
//
//	// Setters and Getters
//	void setSrcStat(Statement* Src);
//	Statement* getSrcStat();
//
//	void setDstStat(Statement* Dst);
//	Statement* getDstStat();
//
//	void setStartPoint(Point P);
//	Point getStartPoint();
//
//	void setEndPoint(Point P);
//	Point getEndPoint();
//
//	void setOutletBranch(int branch);
//	int getOutletBranch() const;
//
//	void SetSelected(bool s);
//	bool IsSelected() const;
//
//	// Update the start and end points based on current statement positions
//	void UpdateConnectionPoints();
//
//	// Draw the connector on the output window
//	void Draw(Output* pOut) const;
//
//	// Check if a point is inside/near the connector (for selection)
//	bool IsPointInConnector(Point p) const;
//
//	// Save connector to file
//	void Save(ofstream& OutFile) const;
//
//	// Load connector from file
//	void Load(ifstream& InFile);
//
//	// Validate the connector (check if it's properly connected)
//	bool Validate(string& errorMsg) const;
//
//	// Destructor
//	~Connector();
//};
//
//#endif

// ==================== Connector.cpp ====================
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
//
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
	// Calculate start and end points based on source and destination statements
	if (SrcStat && DstStat)
	{
		// Get the outlet point from source statement based on branch
		Start = SrcStat->GetOutletPoint(OutletBranch);

		// Get the inlet point from destination statement
		End = DstStat->GetInletPoint();
	}
}

void Connector::Draw(Output* pOut) const
{
	// Draw connector line from source to destination
	// The connector should be drawn highlighted if selected
	if (pOut)
	{
		
		pOut->DrawConnector(Start, End, Selected);
	}
}

bool Connector::IsPointInConnector(Point p) const
{
	// Check if a point is near the connector line (for selection)
	// We consider a tolerance area around the line
	const int TOLERANCE = 5; // pixels

	// Calculate distance from point to line segment
	double dx = End.x - Start.x;
	double dy = End.y - Start.y;

	if (dx == 0 && dy == 0)
	{
		// Start and End are the same point
		double dist = sqrt(pow(p.x - Start.x, 2) + pow(p.y - Start.y, 2));
		return dist <= TOLERANCE;
	}

	// Calculate the parameter t for the closest point on the line
	double t = ((p.x - Start.x) * dx + (p.y - Start.y) * dy) / (dx * dx + dy * dy);

	// Clamp t to [0, 1] to stay within the line segment
	if (t < 0) t = 0;
	if (t > 1) t = 1;

	// Calculate the closest point on the line segment
	double closestX = Start.x + t * dx;
	double closestY = Start.y + t * dy;

	// Calculate distance from point to closest point on line
	double distance = sqrt(pow(p.x - closestX, 2) + pow(p.y - closestY, 2));

	return distance <= TOLERANCE;
}


void Connector::Save(ofstream& OutFile) const
{
	// Save connector information to file
	// Format: Source_Statement_ID Target_Statement_ID Outlet_branch
	if (SrcStat && DstStat)
	{
		OutFile << SrcStat->GetID() << " "
			<< DstStat->GetID() << " "
			<< OutletBranch << endl;
	}
}

void Connector::Load(ifstream& InFile)
{
	// Note: This function typically isn't used directly because
	// connectors are loaded in LoadAction by reading IDs and 
	// finding the corresponding statements, then creating the connector.
	// However, we can load the outlet branch if needed
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

Connector::~Connector()
{
	// Destructor
	// Note: We don't delete SrcStat or DstStat here because they are managed elsewhere
	// The connector only maintains pointers to them
}

