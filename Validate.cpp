#include "Validate.h"
#include "../GUI//Output.h"
Validate::Validate(ApplicationManager* pApp) : Action(pApp)
{
}

void Validate::ReadActionParameters()
{
    // No parameters needed
}
void Validate::Execute()
{
    Output* pOut = pManager->GetOutput();

    if (pManager->IsValid());
    /* pOut->PrintMessage("Flowchart is VALID");*/
    else;
       /* pOut->PrintMessage("Flowchart is NOT valid");*/
}
