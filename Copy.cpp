#include "Copy.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

Copy::Copy(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Copy::ReadActionParameters()
{
	// No parameters to read - copy operates on already selected statement
}

void Copy::Execute()
{
	// Get pointers to Output
	Output* pOut = pManager->GetOutput();

	// Get the currently selected statement
	Statement* pSelectedStat = pManager->GetSelectedStatement();

	if (pSelectedStat != nullptr)
	{
		// Clone the selected statement
		Statement* pClonedStat = pSelectedStat->Clone();

		// Delete old clipboard content if it exists
		Statement* pOldClipboard = pManager->GetClipboard();
		if (pOldClipboard != nullptr)
		{
			delete pOldClipboard;
		}

		// Store the cloned statement in clipboard
		pManager->SetClipboard(pClonedStat);

		// Show success message
		pOut->PrintMessage("Statement copied to clipboard");
	}
	else
	{
		// No statement is selected
		pOut->PrintMessage("No statement selected. Please select a statement first.");
	}
}