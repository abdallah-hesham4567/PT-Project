#pragma once
#include "Action.h"
#include "OperatorAssignment.h"


	class AddOperationAssign : public Action
	{
	private:
		Point Position;	//Position where the user clicks to add the stat.
		string LHS;    //Left Hand Side of the assignment
		string RHS1;    //Right Hand Side of the assignment
		string RHS2;    //Right Hand Side of the assignment
		char op;     //operator of the assignment
	public:
		AddOperationAssign(ApplicationManager* pAppManager);
		//Read Assignemt statements position
		virtual void ReadActionParameters();
		//Create and add an assignemnt statement to the list of statements
		virtual void Execute();
	};

