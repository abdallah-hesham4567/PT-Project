#include "Delete.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Statements\Statement.h"

Delete::Delete(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Delete::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Delete: ready to delete the selected statement...");
}
void Delete::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	Statement* pState = pManager->GetSelectedStatement();

	if (pState == nullptr)
	{
		// No item selected to delete
		pOut->PrintMessage("Delete: No statement selected to delete.");
		return;
	}
	// Delete the selected statement
	pManager->RemoveStatement(pState);      //need to add remove statement in app manager
	// delete the statement from memory
	delete pState;
	// Clear the selection
	pManager->SetSelectedStatement(nullptr);
	// Update the interface
	pManager->UpdateInterface();

	pOut->PrintMessage("Delete: Selected statement deleted.");
}