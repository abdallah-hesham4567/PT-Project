#include "AddConnector.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Connector.h"
#include "..\Actions\Action.h"
AddConnector::AddConnector(ApplicationManager* pAppManager) : Action(pAppManager)
{
	/*SrcStat = nullptr;
	DstStat = nullptr;
	OutletBranch = 0;*/
}

void AddConnector::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	// Step 1: Get the source statement
	pOut->PrintMessage("Add Connector: Click on the SOURCE statement");
	pIn->GetPointClicked(SourcePoint);

	// Find the statement at this point
	SrcStat = pManager->GetStatement(SourcePoint);

	// Validate source statement exists
	if (SrcStat == nullptr)
	{
		pOut->PrintMessage("Error: No statement found at source location. Action cancelled.");
		return;
	}


	// Step 2: Determine outlet branch if needed
	// Check how many outlets the source statement has
	int outletCount = pManager->GetOutConnCount(SrcStat);

	// If source is a conditional statement (has 2 outlets), ask which branch
	if (SrcStat->IsConditional())
	{
		pOut->PrintMessage("Source is conditional. Select outlet branch: 0 for TRUE, 1 for FALSE");

		// Read branch number from user
		string branchStr = pIn->GetString(pOut);

		// Validate branch number
		if (branchStr == "0" || branchStr == "1")
		{
			OutletBranch = stoi(branchStr);
		}
		else
		{
			pOut->PrintMessage("Invalid branch number. Using default (0).");
			OutletBranch = 0;
		}
	}
	else
	{
		// Single outlet (normal statement)
		OutletBranch = 0;
	}

	// Step 3: Get the destination statement
	pOut->PrintMessage("Add Connector: Click on the DESTINATION statement");
	pIn->GetPointClicked(DestPoint);

	// Find the statement at this point
	DstStat = pManager->GetStatement(DestPoint);

	// Validate destination statement exists
	if (DstStat == nullptr)
	{
		pOut->PrintMessage("Error: No statement found at destination location. Action cancelled.");
		return;
	}

	// Validate source and destination are different
	if (SrcStat == DstStat)
	{
		pOut->PrintMessage("Error: Source and destination cannot be the same. Action cancelled.");
		DstStat = nullptr;
		return;
	}

	pOut->ClearStatusBar();
}

void AddConnector::Execute()
{
	// Read the connector parameters
	ReadActionParameters();

	// If parameters are valid, create the connector
	if (SrcStat != nullptr && DstStat != nullptr)
	{
		Output* pOut = pManager->GetOutput();

		// Check if a connector already exists at this outlet
		Connector** existingConns = pManager->GetOutConnectors(SrcStat, OutletBranch);
		if (existingConns != nullptr)
		{
			// Check if any existing connector uses this specific branch
			int existingCount = pManager->GetOutConnCount(SrcStat);
			for (int i = 0; i < existingCount; i++)
			{
				if (existingConns[i]->getOutletBranch() == OutletBranch)
				{
					pOut->PrintMessage("Error: This outlet already has a connector. Delete it first.");
					delete[] existingConns;
					return;
				}
			}
			delete[] existingConns;
		}

		// Create a new connector
		Connector* pConn = new Connector(SrcStat, DstStat, OutletBranch);

		// Add the connector to the application manager
		pManager->AddConnector(pConn);

		// Show success message
		pOut->PrintMessage("Connector added successfully");

		// Update the interface to show the new connector
		pManager->UpdateInterface();
	}
	else
	{
		// Parameters are invalid, action was already cancelled in ReadActionParameters
		// No need to show additional error message
	}
}