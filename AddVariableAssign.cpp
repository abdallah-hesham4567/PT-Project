#include "AddVariableAssign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\HelperFn.h"
#include <sstream>
#include "VariableAssign.h"
using namespace std;

//constructor: set the ApplicationManager pointer inside this action	
AddVariableAssign::AddVariableAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddVariableAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	// 1️⃣ اقرأ موقع النقر
	pOut->PrintMessage("Variable Assignment Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	while (!InDrawingArea(Position))
	{
		pOut->PrintMessage("Invalid position! Click inside the drawing area.");
		pIn->GetPointClicked(Position);
	}
	pOut->ClearStatusBar();
	// 2️⃣ اقرأ LHS من المستخدم وتحقق من صحته
	pOut->PrintMessage("Enter the variable name for LHS:");
	LHS = pIn->GetVariable(pOut);   // GetVariable يضمن اسم متغير صالح
	// 3️⃣ اقرأ RHS من المستخدم وتحقق من صحته
	pOut->PrintMessage("Enter the variable name for RHS:");
	RHS = pIn->GetVariable(pOut);      // GetVariable يضمن اسم متغير صالح
	pOut->ClearStatusBar();  // نظف الرسائل بعد إدخال البيانات
}
void AddVariableAssign::Execute()
{
	ReadActionParameters();
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	VariableAssign* pAssign = new VariableAssign(Corner, LHS, RHS);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}