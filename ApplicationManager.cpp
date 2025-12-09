#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "GUI\Input.h"
#include "GUI\Output.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	StatCount = 0;
	ConnCount = 0;
	SelectedStatement = NULL;	//no Statement is selected yet
	Clipboard = NULL;
	SelectedConnector = NULL;

	//Create an array of Statement pointers and set them to NULL		
	for (int i = 0; i < MaxCount; i++)
	{
		StatList[i] = NULL;
		ConnList[i] = NULL;
	}
	pOut = new Output();
	pIn = pOut->CreateInput();
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount && pConn)
	{
		ConnList[ConnCount++] = pConn;
	}
}

void ApplicationManager::DeleteConnector(Connector* pConn)
{
	if (!pConn) return;

	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == pConn)
		{
			delete ConnList[i];

			// Shift remaining connectors
			for (int j = i; j < ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
			}
			ConnList[ConnCount - 1] = nullptr;
			ConnCount--;

			if (SelectedConnector == pConn)
				SelectedConnector = nullptr;

			return;
		}
	}
}

int ApplicationManager::GetOutConnCount(Statement* pStat) const
{
	if (!pStat) return 0;

	int count = 0;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] && ConnList[i]->getSrcStat() == pStat)
			count++;
	}
	return count;
}

int ApplicationManager::GetInConnCount(Statement* pStat) const
{
	if (!pStat) return 0;

	int count = 0;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] && ConnList[i]->getDstStat() == pStat)
			count++;
	}
	return count;
}


void ApplicationManager::DeleteStatementConnectors(Statement* pStat)
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] &&
			(ConnList[i]->getSrcStat() == pStat || ConnList[i]->getDstStat() == pStat))
		{
			delete ConnList[i];

			for (int j = i; j < ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
			}
			ConnList[ConnCount - 1] = nullptr;
			ConnCount--;
			i--;
		}
	}
}

Connector* ApplicationManager::GetConnectorAtPoint(Point p) const
{
	for (int i = ConnCount - 1; i >= 0; i--)
	{
		if (ConnList[i] && ConnList[i]->IsPointInConnector(p))
		{
			return ConnList[i];
		}
	}
	return nullptr;
}

Statement* ApplicationManager::GetStatementAtPoint(Point p) const
{
	for (int i = StatCount - 1; i >= 0; i--)
	{
		if (StatList[i] && StatList[i]->IsPointInside(p))
		{
			return StatList[i];
		}
	}
	return nullptr;
}

void ApplicationManager::UpdateAllConnectors()
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i])
		{
			ConnList[i]->UpdateConnectionPoints();
		}
	}
}






////////////////////////////////////////////////////////////////////////////////////
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
	case ADD_VALUE_ASSIGN:
		pAct = new AddValueAssign(this);
		break;

	case ADD_CONDITION:
		///create AddCondition Action here

		break;

	case SELECT:
		///create Select Action here

		break;

	case EXIT:
		///create Exit Action here

		break;

	case STATUS:
		return;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement* pStat)
{
	if (StatCount < MaxCount)
		StatList[StatCount++] = pStat;

}

////////////////////////////////////////////////////////////////////////////////////
Statement* ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL


	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement* ApplicationManager::GetSelectedStatement() const
{
	return SelectedStatement;
}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement* pStat)
{
	SelectedStatement = pStat;
}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement* ApplicationManager::GetClipboard() const
{
	return Clipboard;
}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement* pStat)
{
	Clipboard = pStat;
}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for (int i = 0; i < StatCount; i++)
		StatList[i]->Draw(pOut);

	//Draw all connections
	for (int i = 0; i < ConnCount; i++)
		if (ConnList[i])
		ConnList[i]->Draw(pOut);

}

void ApplicationManager::SaveAll(ofstream& OutFile)
{
	// Save statements count
	OutFile << StatCount << endl;

	// Save each statement
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i])
			StatList[i]->Save(OutFile);
	}

	// Save connectors count  // ADD THIS
	OutFile << ConnCount << endl;

	// Save each connector
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i])
			ConnList[i]->Save(OutFile);
	}
}




///		////////////////////////////////////////Validation Function///////////////////////////////////////////	
bool ApplicationManager::Validate() const
{

	// ==============================================
	///		 Ensure single Start and End         
	// ==============================================
	int startCount = 0;
	int endCount = 0;

	// Loop through all statements
	for (int i = 0; i < StatCount; i++)
	{
		// Check if this statement is StartEnd

		StartEnd* SE = dynamic_cast<StartEnd*>(StatList[i]);
		if (SE)
		{
			if (SE->IsStart())
				startCount++;
			else
				endCount++;
		}
	}

	// Check results
	if (startCount != 1)
	{
		pOut->PrintMessage("Error: Flowchart must have exactly ONE Start Statement.");
		return false;
	}

	if (endCount != 1)
	{
		pOut->PrintMessage("Error: Flowchart must have exactly ONE End Statement.");
		return false;
	}

	// ==============================================
	///		 Validate outgoing connectors            
	// ==============================================

	for (int i = 0; i < StatCount; i++)
	{
		Statement* S = StatList[i];

		// 1) Check for Conditional statement (needs 2 connectors)
		Conditional* C = dynamic_cast<Conditional*>(S);
		if (C)
		{
			if (!(C->GetYesConn()) || !(C->GetNoConn()))
			{
				pOut->PrintMessage("Error: Conditional statement must have YES and NO connectors.");
				return false;
			}

			if (C->GetYesConn()->GetDstStat() == nullptr || C->GetNoConn()->GetDstStat() == nullptr) //cheking that both connectors have destination
			{
				pOut->PrintMessage("Error: Conditional connector has no destination.");
				return false;
			}
			continue;
		}

		// 2) Check for Start (needs 1 connector)
		StartEnd* SE = dynamic_cast<StartEnd*>(S);
		if (SE && SE->IsStart())
		{
			if (!(SE->GetConnector()))
			{
				pOut->PrintMessage("Error: Start must have exactly one outgoing connector.");
				return false;
			}
			if (SE->GetConnector()->GetDstStat() == nullptr) //checking that the start connector has destination
			{
				pOut->PrintMessage("Error: Start connector has no destination.");
				return false;
			}

			continue;
		}

		// 3) Check for End (must have 0 connectors)
		if (SE && !SE->IsStart())
		{
			// End must NOT have connector
			if (SE->GetConnector())
			{
				pOut->PrintMessage("Error: End must NOT have an outgoing connector.");
				return false;
			}
			continue;
		}

		// 4) Normal statements (Assignment, Read, Write): must have 1 connector
		if (!(S->GetOutConn()))
		{
			pOut->PrintMessage("Error: Statement is missing an outgoing connector.");
			return false;

		}
		if (S->GetOutConn()->GetDstStat() == nullptr) //checking that the connector has destination
		{
			pOut->PrintMessage("Error: Connector has no destination.");
			return false;
		}
	}


	return true;
}

////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input* ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output* ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < StatCount; i++)
		delete StatList[i];
	for (int i = 0; i < ConnCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;

}