#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "AddCondition.h"
#include "AddRead.h"
#include "AddWrite.h"
#include "AddEnd.h"
#include"AddDeclare.h"
#include "AddStart.h"
#include "AddOperationAssign.h"
#include "AddVariableAssign.h"
#include "AddWhile.h"


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
	if (pConn == nullptr) {
		return;
	}

	// Step 1: Get source and destination statements
	Statement* pSrcStat = pConn->getSrcStat();
	Statement* pDstStat = pConn->getDstStat();

	// Step 2: Clear the source statement's outgoing connector pointer
	if (pSrcStat != nullptr) {
		pSrcStat->SetOutConn(nullptr);
	}

	// Step 3: Remove from destination statement's incoming connectors list
	if (pDstStat != nullptr) {
		pDstStat->RemoveIncomingConnector(pConn);
	}

	// Step 4: Remove connector from the ConnectorList
	for (int i = 0; i < ConnCount; i++) {
		if (ConnList[i] == pConn) {
			// Shift all connectors after this one to the left
			for (int j = i; j < ConnCount - 1; j++) {
				ConnList[j] = ConnList[j + 1];
			}
			ConnCount--;
			break;
		}
	}

	// Step 5: Delete the connector object
	delete pConn;
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
void ApplicationManager::DeleteStatement(Statement* statement) {
	if (statement == nullptr) {
		return;
	}

	// STEP A: Delete its outgoing connector
	Connector* outgoingConn = statement->GetOutConn();
	if (outgoingConn != nullptr) {
		// Remove from destination statement's incoming list
		Statement* dstStmt = outgoingConn->getDstStat();
		if (dstStmt != nullptr) {
			dstStmt->RemoveIncomingConnector(outgoingConn);
		}

		// Remove from manager and delete
		DeleteConnector(outgoingConn);
		delete outgoingConn;
	}

	// STEP B: Delete all incoming connectors
	// Important: Create a copy of the vector because we're modifying it during iteration
	 vector<Connector*> incomingConnectors = statement->GetIncomingConnectors();

	for (Connector* incomingConn : incomingConnectors) {
		if (incomingConn != nullptr) {
			// Clear the source statement's outgoing connector pointer
			Statement* srcStmt = incomingConn->getSrcStat();
			if (srcStmt != nullptr) {
				srcStmt->SetOutConn(nullptr);
			}

			// Remove from manager and delete
			pAppMgr->RemoveConnector(incomingConn);
			delete incomingConn;
		}
	}

	// STEP C: Delete the statement itself
	pAppMgr->RemoveStatement(statement);
	delete statement;
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

void ApplicationManager::UnselectAll()
{
	for (auto s : StatList)
		s->SetSelected(false);
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
		pAct = new AddCondition(this);
		break;

	case ADD_START:
			pAct = new AddStart(this);
			break;

	case ADD_END:
		pAct = new AddEnd(this);
		break;

	case ADD_DECLARE_VARIABLE:
		pAct = new AddDeclare(this);
		break;
////////////
	case ADD_VAR_ASSIGN:
		pAct = new AddVariableassign(this);
		break;
//////////////////

	case ADD_OPER_ASSIGN:
		pAct = new AddOperationAssign(this);
		break;

	case ADD_LOOP:
		pAct = new AddWhile(this);
		break;

	case ADD_READ:
		pAct = new AddRead(this);
		break;

	case ADD_WRITE:
		pAct = new AddWrite(this);
		break;

	case ADD_CONNECTOR:
		pAct = new AddConnector(this);
		break;

	case EDIT_STAT:
		pAct = new Edit(this);
		break;

	case DEL:
		pAct = new Delete(this);
		break;

	case COPY:
		pAct = new Copy(this);
		break;

	case CUT:
		pAct = new Cut(this);
		break;

	case PASTE:
		pAct = new Paste(this);
		break;

	case SAVE:
		pAct = new Save(this);
		break;

	case LOAD:
		pAct = new Load(this);
		break;

	case SWITCH_DSN_MODE:
	{
		//// remove toolbar and switch 
	}

	case SWITCH_SIM_MODE:
	{
		//// remove toolbar and switch 
	}

	case UNDO:
		pAct = new UNDO(this);
		break;
	case REDO:
		pAct = new REDO(this);
		break;
	case VALIDATE:
		pAct = new Validate(this);
		break;





	case RUN:
		///create Select Action here
		pAct = new Run(this);
		break;

	case EXIT:
		///create Exit Action here
		pAct = new Exit(this);
		break;
	case EXITS:
		///create Exit Action here
		pAct = new Exit(this);
		break;
	case CPP:
		///create Exit Action here
		pAct = new Cpp(this);
		break;

	case DRAWING_AREA:
	{
		//// write on status bar
	}
	case OUTPUT_AREA:
	{
		//// write on status bar
	}
	case DSN_TOOL:
	{
		//// write on status bar
	}
	case SIM_TOOL:
	{
		//// write on status bar
	}

	
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




void ApplicationManager::LoadAll(const string& filename)
{
	ifstream InFile(filename);
	if (!InFile.is_open())
	{
		// Show error message
		return;
	}

	// Clear existing statements
	ClearAll();

	// Load statement count
	int statCount;
	InFile >> statCount;

	// Map to store statements by ID
	map<int, Statement*> statMap;

	// Load all statements
	for (int i = 0; i < statCount; i++)
	{
		string type;
		InFile >> type;

		Statement* pStat = nullptr;

		if (type == "STRT")
			pStat = new Start();
		else if (type == "DECLARE")
			pStat = new Declare();
		else if (type == "READ")
			pStat = new Read();
		else if (type == "COND")
			pStat = new Condition();
		else if (type == "OP_ASSIGN")
			pStat = new OperationAssign();
		else if (type == "WRITE")
			pStat = new Write();
		else if (type == "END")
			pStat = new End();

		if (pStat)
		{
			pStat->Load(InFile);
			StatementList.push_back(pStat);
			statMap[pStat->getID()] = pStat;
		}
	}

	// Load connector count
	int connCount;
	InFile >> connCount;

	// Load and recreate connectors
	for (int i = 0; i < connCount; i++)
	{
		int srcID, dstID, branch;
		InFile >> srcID >> dstID >> branch;

		// Recreate connector between statements
		Statement* src = statMap[srcID];
		Statement* dst = statMap[dstID];

		if (src && dst)
		{
			// Create connector based on branch type
			// This depends on your connector creation logic
		}
	}

	InFile.close();

	// Update display
	UpdateInterface();
}




