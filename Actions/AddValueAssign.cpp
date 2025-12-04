#include "AddValueAssign.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddValueAssign::AddValueAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}




void AddValueAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	// 1️⃣ اقرأ موقع النقر
	pOut->PrintMessage("Value Assignment Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	// 2️⃣ اقرأ LHS من المستخدم وتحقق من صحته
	pOut->PrintMessage("Enter the variable name for LHS:");
	LHS = pIn->GetVariable(pOut);   // GetVariable يضمن اسم متغير صالح

	// 3️⃣ اقرأ RHS من المستخدم وتحقق من صحته
	pOut->PrintMessage("Enter the value for RHS:");
	RHS = pIn->GetValue(pOut);      // GetValue يضمن قيمة رقمية صحيحة

	pOut->ClearStatusBar();  // نظف الرسائل بعد إدخال البيانات
}



void AddValueAssign::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	ValueAssign* pAssign = new ValueAssign(Corner, LHS, RHS);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}