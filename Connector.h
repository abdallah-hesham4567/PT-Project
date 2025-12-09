#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "GUI\UI_Info.h"
#include "GUI\output.h"
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	bool Selected;       // True if connector is selected
	int BranchType;    // 0 for normal, 1 for YES branch, 2 for NO branch (for conditional statements)

public:
	// Constructor: creates a connector between two statements
	Connector(Statement* Src, Statement* Dst, int outletBranch = 0);

	// Setters and Getters
	void setSrcStat(Statement* Src);
	Statement* getSrcStat();

	void setDstStat(Statement* Dst);
	Statement* getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void setOutletBranch(int branch);
	int getOutletBranch() const;

	void SetSelected(bool s);
	bool IsSelected() const;

	// Update the start and end points based on current statement positions
	void UpdateConnectionPoints();

	// Draw the connector on the output window
	void Draw(Output* pOut) const;

	// Check if a point is inside/near the connector (for selection)
	bool IsPointInConnector(Point p) const;

	// Save connector to file
	void Save(ofstream& OutFile) const;

	// Load connector from file
	void Load(ifstream& InFile);

	int getBranchType() const { return BranchType; }

	// Validate the connector (check if it's properly connected)
	bool Validate(string& errorMsg) const;

	// Destructor
	~Connector();
};

#endif