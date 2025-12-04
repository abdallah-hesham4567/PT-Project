#include "AddOperationAssign.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\HelperFn.h"
#include <sstream>
using namespace std;
//constructor: set the ApplicationManager pointer inside this action

AddOperationAssign::AddOperationAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddOperationAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	// 1️⃣ اقرأ موقع النقر
	pOut->PrintMessage("Operator Assignment Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	// 2️⃣ اقرأ LHS من المستخدم وتحقق من صحته
	pOut->PrintMessage("Enter the variable name for LHS:");
	LHS = pIn->GetVariable(pOut);   // GetVariable يضمن اسم متغير صالح
	// 3️⃣ اقرأ RHS1 من المستخدم وتحقق من صحته
	pOut->PrintMessage("Enter the first operand for RHS:");
	RHS1 = pIn->GetVariableOrVal(pOut);      // GetVariable يضمن اسم متغير صالح
	// 4️⃣ اقرأ operator من المستخدم وتحقق من صحته
	pOut->PrintMessage("Enter the operator (+, -, *, /):");
	op = pIn->GetArithOperator(pOut);      // GetOperator يضمن عامل صالح
	// 5️⃣ اقرأ RHS2 من المستخدم وتحقق من صحته
	pOut->PrintMessage("Enter the second operand for RHS:");
	RHS2 = pIn->GetVariableOrVal(pOut);      // GetVariable يضمن اسم متغير صالح
	pOut->ClearStatusBar();  // نظف الرسائل بعد إدخال البيانات
}

void AddOperationAssign::Execute()
{
	ReadActionParameters();
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;
	OperatorAssignment* pAssign = new OperatorAssignment(Corner, LHS, RHS1, op, RHS2);
	pManager->AddStatement(pAssign);
	// Adds the created statement to application manger's statement list
}




