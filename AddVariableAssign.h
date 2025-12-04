#ifndef ADD_VARIABLE_ASSIGN_H
#define ADD_VARIABLE_ASSIGN_H

#include "Action.h"


class AddVariableAssign : public Action 
{
private:
	Point Position;	// Position where the user clicks to add the stat.
	string LHS; // Left Hand Side of the assignment
	string RHS; // Right Hand Side of the assignment
public:
	AddVariableAssign(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();	


};

#endif

































#endif
