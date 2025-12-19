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
#include "Action.h"
#include "ActionSelect.h"
#include "Delete.h"
#include "Copy.h"
#include "Cut.h"
#include "Paste.h"
#include "Edit.h"
#include "ActionSave.h"
#include "VariableAssign.h"
#include "ActionLoad.h"
#include "Variable.h"
#include "Run.h"
#include "Validate.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	RunStartup();
	//Initialize StatCount and ConnCount
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

//int ApplicationManager::GetOutConnCount(Statement* pStat) const
//{
//	if (pStat->IsConditional())
//		return 2;
//	if (!pStat) return 0;
//	return 1;
//}

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

void ApplicationManager::DeleteConnector(Connector* pConn)
{
	if (pConn == nullptr)
		return;

	// Find and delete the connector from ConnList
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == pConn)
		{
			// Delete the connector object
			delete ConnList[i];

			// Shift remaining connectors left
			for (int j = i; j < ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
			}

			// Decrease count
			ConnCount--;
			break;  // Connector found and deleted
		}
	}
}


void ApplicationManager::DeleteStatementConnectors(Statement* pStat)
{
	if (pStat == nullptr)
		return;

	// Loop through all connectors
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] != nullptr)
		{
			// Check if this connector is connected to the statement
			if (ConnList[i]->getSrcStat() == pStat || ConnList[i]->getDstStat() == pStat)
			{
				// Delete this connector using DeleteConnector function
				DeleteConnector(ConnList[i]);

				// Adjust index since DeleteConnector shifts the array
				i--;
			}
		}
	}

}

void ApplicationManager::DeleteStatement(Statement* statement) 
{
	if (statement == nullptr) {
		return;
	}

	DeleteStatementConnectors(statement);

	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] == statement)
		{
			// Delete the statement object
			delete StatList[i];

			// Shift remaining statements left
			for (int j = i; j < StatCount - 1; j++)
			{
				StatList[j] = StatList[j + 1];
			}

			// Decrease count
			StatCount--;
			break;  // Statement found and deleted
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

void ApplicationManager::UnselectAll()
{
	
	for (int i=0 ; i< StatCount ;i++)
	{ 
		if (StatList[i])
			StatList[i]->SetSelected(false);
	}
		

	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i])
			ConnList[i]->SetSelected(false);
	}
	
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
		pAct = new AddVariableAssign(this);
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
		pAct = new ::AddConnector(this);
		break;

	case SELECT:
		pAct = new ActionSelect(this);
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
		pAct = new ActionSave(this);
	break;

	case LOAD:
		pAct = new ActionLoad(this);
		break;

	case SWITCH_DSN_MODE:
	{
		//// remove toolbar and switch 
		pOut->ClearOutputBar();
		pOut->Clear_SimulationToolBar();
		pOut->CreateDesignToolBar();
		break;
	}

	case SWITCH_SIM_MODE:
	{
		//// remove toolbar and switch 
		pOut->ClearOutputBar();
		pOut->Clear_DesignToolBar();
		pOut->CreateSimulationToolBar();
		break;
	}
	case CLEAR:
	{
		///create Clear Action here
		this->ClearAll();
		pOut->PrintMessage("All Cleared !");
		break;
		
	}
	case EDIT_STAT:
	pAct = new Edit(this);
	break;

	case GITHUB:
	{
		///create Github Action here
		pOut->PrintMessage("Redirecting to GitHub...");
		ShellExecuteA(NULL, "open", "https://github.com/abdallah-hesham4567/PT-Project.git", NULL, NULL, SW_SHOWNORMAL);
		break;
	}


	case RUN:
		///create Select Action here
		pOut->ClearOutputBar();
		pAct = new Run(this);
		break;

	case VALIDATE:
		pAct = new Validate(this);
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

//////////////////////////////////////////////////////////////////////////////////////
//Statement* ApplicationManager::GetStatement(Point P) const
//{
//	//If this point P(x,y) belongs to a statement return a pointer to it.
//	//otherwise, return NULL
//
//
//	///Add your code here to search for a statement given a point P(x,y)	
//	///WITHOUT breaking class responsibilities
//
//	return NULL;
//}

Statement* ApplicationManager::GetStatement(Point P) const
{
	// Loop through all statements
	for (int i = 0; i < StatCount; i++) // Assuming StatCount is the number of statements
	{
		Statement* stat = StatList[i]; // Assuming StatementsList is an array of Statement*
		// Use the virtual function implemented in each statement
		if (stat->IsPointInside(P))
			return stat; // Return the statement containing the poin
	}

	// If no statement contains the point
	return nullptr;
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
	if (Clipboard) delete Clipboard;
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
bool ApplicationManager::IsValid() const
{
	Output* pOut = GetOutput();
	string errorMsg = "";

	// ============================================
	// PHASE 1: STRUCTURE VALIDATION (Same as before)
	// ============================================

	// Validation Rule 1: Must have exactly ONE Start statement
	int startCount = 0;
	Statement* startStat = nullptr;

	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->getStatementType() == "STRT")
		{
			startCount++;
			startStat = StatList[i];  // Store the Start statement
		}
	}

	if (startCount != 1)
	{
		errorMsg = "Error: Flowchart must have exactly ONE Start statement.";
		pOut->PrintMessage(errorMsg);
		return false;
	}

	// Validation Rule 2: Must have exactly ONE End statement
	int endCount = 0;

	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->getStatementType() == "END")
		{
			endCount++;
		}
	}

	if (endCount != 1)
	{
		errorMsg = "Error: Flowchart must have exactly ONE End statement.";
		pOut->PrintMessage(errorMsg);
		return false;
	}

	// Validation Rule 3: Check connectivity (same as before)
	for (int i = 0; i < StatCount; i++)
	{
		Statement* pStat = StatList[i];
		string statType = pStat->getStatementType();

		// Check input connectors (except Start)
		if (statType != "STRT")
		{
			int inCount = GetInConnCount(pStat);
			if (inCount == 0)
			{
				errorMsg = "Error: Statement has no input connector (orphaned statement).";
				pOut->PrintMessage(errorMsg);
				return false;
			}
		}

		// Check output connectors (except End)
		if (statType != "END")
		{
			int outCount = GetOutConnCount(pStat);

			// Conditional/While must have 2 outputs
			if (statType == "COND" || statType == "WHILE")
			{
				if (outCount != 2)
				{
					errorMsg = "Error: Conditional statement must have exactly 2 output connectors.";
					pOut->PrintMessage(errorMsg);
					return false;
				}

				// Check branches 0 and 1 exist
				Connector** outConns = GetOutConnectors(pStat);
				bool hasBranch2 = false;
				bool hasBranch1 = false;

				for (int j = 0; j < outCount; j++)
				{
					if (outConns[j]->getOutletBranch() == 2)
						hasBranch2 = true;
					if (outConns[j]->getOutletBranch() == 1)
						hasBranch1 = true;
				}

				delete[] outConns;

				if (!hasBranch2 || !hasBranch1)
				{
					errorMsg = "Error: Conditional must have both TRUE (1) and FALSE (2) branches.";
					pOut->PrintMessage(errorMsg);
					return false;
				}
			}
			else
			{
				// Normal statements must have exactly 1 output
				if (outCount != 1)
				{
					errorMsg = "Error: Statement must have exactly 1 output connector.";
					pOut->PrintMessage(errorMsg);
					return false;
				}
			}
		}
		else  // End statement
		{
			int outCount = GetOutConnCount(pStat);
			if (outCount > 0)
			{
				errorMsg = "Error: End statement cannot have output connectors.";
				pOut->PrintMessage(errorMsg);
				return false;
			}
		}
	}

	// Validation Rule 4: Validate all connectors
	for (int i = 0; i < ConnCount; i++)
	{
		if (!ConnList[i]->Validate(errorMsg))
		{
			pOut->PrintMessage("Error: Invalid connector - " + errorMsg);
			return false;
		}
	}


	// VARIABLE VALIDATION IN EXECUTION ORDER
	// =================================================================================================================================================

	// Track declared variables
	string declaredVars[100];
	int declaredCount = 0;

	// infinite loop detection
	bool visited[200] = { false }; 
	int visitCount = 0;

	// Start from START statement
	Statement* currentStat = startStat;

	// Loop until we reach END or detect infinite loop
	while (currentStat != nullptr && currentStat->getStatementType() != "END")
	{
		// Check for infinite loop (visited too many statements)
		visitCount++;
		if (visitCount > StatCount * 2)
		{
			errorMsg = "Error: Possible infinite loop detected in flowchart.";
			pOut->PrintMessage(errorMsg);
			return false;
		}

		// Get statement type
		string statType = currentStat->getStatementType();

		// Skip Start statement (no variable logic)
		if (statType != "STRT")
		{
			if (statType == "READ" || statType == "DECLARE")
			{
				string varName = currentStat->GetVariableName();

				// Check for duplicate declaration
				bool alreadyDeclared = false;
				for (int j = 0; j < declaredCount; j++)
				{
					if (declaredVars[j] == varName)
					{
						alreadyDeclared = true;
						break;
					}
				}

				if (alreadyDeclared)
				{
					errorMsg = "Error: Variable '" + varName + "' is already declared.";
					pOut->PrintMessage(errorMsg);
					return false;
				}

				// Add to declared list
				declaredVars[declaredCount++] = varName;
			}
			// WRITE Statement

			else if (statType == "WRITE")
			{
				string varName = currentStat->GetVariableName();
				
				if (varName.size() >= 2 && varName.front() == '"' && varName.back() == '"')
				{
					//means that the given string is literal and skip varibale check 
				}
				else if (IsValue(varName))
				{
					// Literal value skip variable check
				}
				else
				{
					// Check if variable exists
					bool exists = false;
					for (int j = 0; j < declaredCount; j++)
					{
						if (declaredVars[j] == varName)
						{
							exists = true;
							break;
						}
					}

					if (!exists)
					{
						errorMsg = "Error: Variable '" + varName + "' is not declared.";
						pOut->PrintMessage(errorMsg);
						return false;
					}
				}
				
			}

			// value assign Statement
			else if (statType == "VALASSIGN")
			{
				string lhs = currentStat->GetLHS();


				// Check if LHS already declared
				bool exists = false;
				for (int j = 0; j < declaredCount; j++)
				{
					if (declaredVars[j] == lhs)
					{
						exists = true;
						break;
					}
				}

				//declare LHS if not declared
				if (!exists)
				{
					declaredVars[declaredCount++] = lhs;
				}
			}

			//variable assign
			else if (statType == "VAR_ASSIGN")
			{
				string lhs = currentStat->GetLHS();
				string rhs = currentStat->GetRHS();

				// Check if LHS already declared
				bool exists = false;
				for (int j = 0; j < declaredCount; j++)
				{
					if (declaredVars[j] == lhs)
					{
						exists = true;
						break;
					}
				}

				//declare LHS if not declared
				if (!exists)
				{
					declaredVars[declaredCount++] = lhs;
				}

				
				// Check if RHS already declared
				exists = false;
				for (int j = 0; j < declaredCount; j++)
				{
					if (declaredVars[j] == rhs)
					{
						exists = true;
						break;
					}
				}
			}

			// operation assign statement
			else if (statType == "OP_ASSIGN")
			{
				string lhs = currentStat->GetLHS();
				string rhs1 = currentStat->GetRHS();
				string rhs2 = currentStat->GetRHS2();

				// Check if LHS is declared
				bool exists = false;
				for (int j = 0; j < declaredCount; j++)
				{
					if (declaredVars[j] == lhs)
					{
						exists = true;
						break;
					}
				}

			}
			//CONDITIONAL or WHILE Statement
			else if (statType == "COND" || statType == "WHILE")
			{
				// TODO: Check variables in condition
				// For now, skip
			}
		}

		// === MOVE TO NEXT STATEMENT ===

		// Find output connector(s)
		int outCount = GetOutConnCount(currentStat);

		if (outCount == 0)
		{
			// Reached end (or error - should be caught earlier)
			break;
		}
		else if (outCount == 1)
		{
			// Normal statement - follow the single connector
			Connector** outConns = GetOutConnectors(currentStat);
			if (outConns != nullptr && outConns[0] != nullptr)
			{
				currentStat = outConns[0]->getDstStat();
			}
			else
			{
				currentStat = nullptr;
			}
			delete[] outConns;
		}
		else if (outCount == 2)
		{
			// Conditional - for validation, follow TRUE branch (branch 0)
			// In real execution, you'd evaluate the condition
			Connector** outConns = GetOutConnectors(currentStat);

			Statement* nextStat = nullptr;
			for (int i = 0; i < outCount; i++)
			{
				if (outConns[i]->getOutletBranch() == 0)
				{
					nextStat = outConns[i]->getDstStat();
					break;
				}
			}

			currentStat = nextStat;
			delete[] outConns;
		}
		else
		{
			// Invalid number of outputs (should be caught earlier)
			break;
		}
	}

	// All checks passed
	pOut->PrintMessage("Validation successful!");
	return true;
}

Statement* ApplicationManager::GetNextStatement(Statement* pStat)
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getSrcStat() == pStat)
			return ConnList[i]->getDstStat();
	}
	return nullptr;
}

Statement* ApplicationManager::GetNextAfterCondition(Statement* pStat, bool result)
{
	int wantedBranch;

	if (result == true)
		wantedBranch = 1;
	else
		wantedBranch = 2;

	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getSrcStat() == pStat &&
			ConnList[i]->getOutletBranch() == wantedBranch)
		{
			return ConnList[i]->getDstStat();
		}
	}

	return nullptr;
}

void ApplicationManager::RunSimulation()
{
	Variable Vars[100];
	int VarCount = 0;

	Statement* pCurrent = nullptr;

	for (int i = 0; i < StatCount; i++)
	{
		if (dynamic_cast<Start*>(StatList[i]))
		{
			pCurrent = StatList[i];
			break;
		}
	}
	while (!dynamic_cast<End*>(pCurrent))
	{
		// لو Condition
		if (auto pCond = dynamic_cast<ConditionStatement*>(pCurrent))
		{
			bool res = pCond->Evaluate(Vars, VarCount);
			pCurrent = GetNextAfterCondition(pCond, res);
			continue;
		}

		// لو While
		if (auto pWhile = dynamic_cast<WhileStatement*>(pCurrent))
		{
			bool res = pWhile->Evaluate(Vars, VarCount);
			pCurrent = GetNextAfterCondition(pWhile, res);
			continue;
		}

		// أي Statement عادي
		pCurrent->Execute(Vars, VarCount, pIn, pOut);
		pCurrent = GetNextStatement(pCurrent);
	}


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



void ApplicationManager::LoadAll(ifstream& InFile)
{

	// Clear existing flowchart first
	ClearAll();

	// Read number of statements
	int statCount;
	InFile >> statCount;

	// Load all statements
	for (int i = 0; i < statCount; i++)
	{
		string StatType;
		InFile >> StatType;

		Statement* pStat = nullptr;
		Point p (0,0);

		// Create statement using load constructor (pass ifstream)
		if (StatType == "STRT")
			pStat = new Start(p);
		else if (StatType == "END")
			pStat = new End(p);
		else if (StatType == "DECLARE")
			pStat = new DeclareStatement(p);
		else if (StatType == "VALUE_ASSIGN")
			pStat = new ValueAssign(p);
		else if (StatType == "VAR_ASSIGN")
			pStat = new VariableAssign(p);
		else if (StatType == "OP_ASSIGN")
			pStat = new OperatorAssignment(p);
		else if (StatType == "COND")
			pStat = new ConditionStatement(p);
		else if (StatType == "WHILE")
			pStat = new WhileStatement(p);
		else if (StatType == "READ")
			pStat = new Read(p);
		else if (StatType == "WRITE")
			pStat = new Write(p);

		if (pStat)
		{
			pStat->Load(InFile);
			AddStatement(pStat);
		}
		
	}

	// Read number of connectors
	int connCount;
	InFile >> connCount;

	// Load all connectors
	for (int i = 0; i < connCount; i++)
	{
		int SrcID, DstID, OutletBranch;
		InFile >> SrcID >> DstID >> OutletBranch;

		Statement* pSrc = GetStatementWithID(SrcID);
		Statement* pDst = GetStatementWithID(DstID);

		if (pSrc && pDst)
		{
			Connector* pConn = new Connector(pSrc, pDst, OutletBranch);

			// Check if source is a conditional statement
			ConditionStatement* pCond = dynamic_cast<ConditionStatement*>(pSrc);
			WhileStatement *pWhile = dynamic_cast<WhileStatement*>(pSrc);
			if (pCond)  // Source is a conditional statement
			{
				if (OutletBranch == 1)  // YES/TRUE branch
				{
					pCond->setTrueBranch(pConn);
				}
				else if (OutletBranch == 2)  // NO/FALSE branch
				{
					pCond->setFalseBranch(pConn);
				}
			}

			else if (pWhile)  // Source is a conditional statement
			{
				if (OutletBranch == 1)  // YES/TRUE branch
				{
					pWhile->setTrueBranch(pConn);
				}
				else if (OutletBranch == 2)  // NO/FALSE branch
				{
					pWhile->setFalseBranch(pConn);
				}
			}

			else  // Source is a normal statement
			{
				pSrc->SetOutConn(pConn);
			}

			// Set input connector for destination
			pDst->SetInConn(pConn);

			// Add to connector list
			AddConnector(pConn);
		}
	}
}





Statement* ApplicationManager::GetStatementWithID(int id) const
{
	for (auto s : StatList)
	{
		if (s->GetID() == id)
			return s;
	}
	return nullptr;
}

















Connector** ApplicationManager::GetOutConnectors(Statement* pStat) const
{
	int count;
	if (pStat == nullptr)
	{
		count = 0;
		return nullptr;
	}

	// First, count how many output connectors this statement has
	count = 0;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] != nullptr && ConnList[i]->getSrcStat() == pStat)
		{
			count++;
		}
	}

	// If no connectors found, return nullptr
	if (count == 0)
	{
		return nullptr;
	}

	// Allocate array to hold the connector pointers
	Connector** outConnectors = new Connector * [count];

	// Fill the array with the connectors
	int index = 0;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] != nullptr && ConnList[i]->getSrcStat() == pStat)
		{
			outConnectors[index] = ConnList[i];
			index++;
		}
	}

	return outConnectors;
}


// Get all input connectors to a statement
Connector** ApplicationManager::GetInConnectors(Statement* pStat, int& count) const
{
	if (pStat == nullptr)
	{
		count = 0;
		return nullptr;
	}

	// First, count how many input connectors this statement has
	count = 0;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] != nullptr && ConnList[i]->getDstStat() == pStat)
		{
			count++;
		}
	}

	// If no connectors found, return nullptr
	if (count == 0)
	{
		return nullptr;
	}

	// Allocate array to hold the connector pointers
	Connector** inConnectors = new Connector * [count];

	// Fill the array with the connectors
	int index = 0;
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] != nullptr && ConnList[i]->getDstStat() == pStat)
		{
			inConnectors[index] = ConnList[i];
			index++;
		}
	}

	return inConnectors;
}

int ApplicationManager::GetUsedBranch(Statement* src)
{
	int count = GetOutConnCount(src);
	Connector** conns = GetOutConnectors(src);

	for (int i = 0; i < count; i++)
	{
		if (conns[i] != nullptr)
			return conns[i]->getOutletBranch(); // 1 or 2
	}

	return 0;
}
bool ApplicationManager::CanPlaceStatement(Point p, int w, int h) const
{
	if (!InDrawingArea(p, w, h))
		return false;

	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->IsOverlapping(p, w, h))
			return false;
	}

	return true;
}

void ApplicationManager::ClearAll()
{
	// Delete all statements
	for (int i = 0; i < StatCount; i++)
	{
		delete StatList[i];
		StatList[i] = nullptr;
	}
	StatCount = 0;

	// Delete all connectors
	for (int i = 0; i < ConnCount; i++)
	{
		delete ConnList[i];
		ConnList[i] = nullptr;
	}
	ConnCount = 0;

	// Clear clipboard if needed
	if (Clipboard != nullptr)
	{
		delete Clipboard;
		Clipboard = nullptr;
	}
}

void ApplicationManager::RunStartup()
{
	int x, y;
	pOut->ShowStartupScreen();

	while (true)
	{
		Point p;
		pIn->GetPointClicked(p);
		int btnW = 260;
		int btnH = 50;
		int btnX = 100 + (1366 / 2) - btnW / 2;
		// Start Program
		if (p.x >= btnX && p.x <= btnX + btnW &&
			p.y >= 300 && p.y <= 300 + btnH)
		{
			pOut->ClearDrawArea();
			pOut->CreateDesignToolBar();
			pOut->CreateStatusBar();
			pOut->ClearOutputBar();
			pOut->PrintMessage("Welcome to the Flowchart Programming Tool!");
			break;
		}

		// Student Info
		else if (p.x >= btnX && p.x <= btnX + btnW &&
			p.y >= 370 && p.y <= 370 + btnH)
		{
			ShellExecuteA(NULL, "open", "Names.txt", NULL, NULL, SW_SHOWNORMAL);
		}

		// GitHub
		else if (p.x >= btnX && p.x <= btnX + btnW &&
			p.y >= 440 && p.y <= 440 + btnH)
		{
			ShellExecuteA(NULL, "open",
				"https://github.com/abdallah-hesham4567/PT-Project.git",
				NULL, NULL, SW_SHOWNORMAL);
		}
		// Exit
		else if (p.x >= btnX && p.x <= btnX + btnW &&
			 p.y >= 510 && p.y <= 510 + btnH)
		{
			exit(0);
		}
	}
}

