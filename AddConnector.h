#ifndef ADD_CONNECTOR_H
#define ADD_CONNECTOR_H

#include "Action.h"
#include "..\Statements\Statement.h"

// Add Connector Action
// This class is responsible for:
// 1 - Getting the source statement from the user (first click)
// 2 - Getting the destination statement from the user (second click)
// 3 - Getting the outlet branch number if source has multiple outlets
// 4 - Creating a Connector object
// 5 - Adding the connector to the application manager
class AddConnector : public Action
{
private:
	Point SourcePoint;      // Position where user clicks for source statement
	Point DestPoint;        // Position where user clicks for destination statement
	Statement* SrcStat;     // Pointer to source statement
	Statement* DstStat;     // Pointer to destination statement
	int OutletBranch;       // Which outlet of the source statement (0 for single, 0/1 for conditional)

public:
	AddConnector(ApplicationManager* pAppManager);

	// Read connector parameters (source and destination statements)
	virtual void ReadActionParameters() ;

	// Create and add a connector to the list of connectors
	virtual void Execute();
};

#endif