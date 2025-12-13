#include "Edit.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Edit::Edit(ApplicationManager* pApp)
    : Action(pApp)
{
}

void Edit::ReadActionParameters()
{
	// No parameters to read for Edit action    
}

void Edit::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    Statement* s = pManager->GetSelectedStatement();

    if (!s)
    {
        pOut->PrintMessage("Please select a statement first");
        return;
    }
    s->Edit(pIn, pOut);
}
