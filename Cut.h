#ifndef CUT_H
#define CUT_H

#include "Action.h"

class Copy;

// Cut Action Class
// Copies the currently selected statement to clipboard AND deletes it
// Also deletes all connectors attached to the statement
// Does NOT copy connectors to clipboard - only the statement itself
// Overwrites previous clipboard content
class Cut : public Action
{
public:
	Cut(ApplicationManager* pAppManager);
	virtual void ReadActionParameters() override {};
	// Execute the cut operation (copy + delete)
	virtual void Execute();
};

#endif