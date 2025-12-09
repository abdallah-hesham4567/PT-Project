#include "Delete.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

Delete::Delete(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Delete::ReadActionParameters()
{
	// No parameters to read - delete operates on already selected item
	// The selection is already stored in ApplicationManager
}

void Delete::Execute()
{
	// Get pointers to Input/Output
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// Check if a statement is selected
	Statement* pSelectedStat = pManager->GetSelectedStatement();

	if (pSelectedStat != nullptr)
	{
		// Delete the selected statement
		// This will also delete all connectors attached to it
		pManager->DeleteStatement(pSelectedStat);

		// Clear the selection
		pManager->SetSelectedStatement(nullptr);

		// Show success message
		pOut->PrintMessage("Statement deleted successfully");
	}
	else
	{
		// Check if a connector is selected
		Connector* pSelectedConn = pManager->GetSelectedConnector();

		if (pSelectedConn != nullptr)
		{
			// Delete only the connector
			pManager->DeleteConnector(pSelectedConn);

			// Clear the selection
			pManager->SetSelectedConnector(nullptr);

			// Show success message
			pOut->PrintMessage("Connector deleted successfully");
		}
		else
		{
			// Nothing is selected
			pOut->PrintMessage("No statement or connector selected. Please select an item first.");
		}
	}

	// Update the interface
	pManager->UpdateInterface();
}