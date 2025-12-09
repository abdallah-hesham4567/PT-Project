#ifndef COPY_H
#define COPY_H

#include "Action.h"

// Copy Action Class
// Copies the currently selected statement to the clipboard
// Does NOT copy connectors - only the statement itself
// Overwrites previous clipboard content
class Copy : public Action
{
public:
	Copy(ApplicationManager* pAppManager);

	// No parameters needed - operates on already selected statement
	virtual void ReadActionParameters();

	// Execute the copy operation
	virtual void Execute();
};

#endif