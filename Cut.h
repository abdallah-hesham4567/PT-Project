#ifndef CUT_H
#define CUT_H

#include "Action.h"

// Cut Action Class
// Copies the currently selected statement to clipboard AND deletes it
// Also deletes all connectors attached to the statement
// Does NOT copy connectors to clipboard - only the statement itself
// Overwrites previous clipboard content
class Cut : public Action
{
public:
	Cut(ApplicationManager* pAppManager);

	// No parameters needed - operates on already selected statement
	virtual void ReadActionParameters();

	// Execute the cut operation (copy + delete)
	virtual void Execute();
};

#endif