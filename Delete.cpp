#include "Delete.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

Delete::Delete(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Delete::ReadActionParameters()
{
	// No parameters to read for delete action
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Delete: Deleting the selected item...");
}
