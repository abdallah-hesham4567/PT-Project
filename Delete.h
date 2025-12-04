#ifndef DELETE_H
#define DELETE_H

#include "Action.h"

// Delete Action Class
// Deletes the currently selected statement or connector
// If statement is deleted, all connectors attached to it are also deleted
class Delete : public Action
{
public:
	Delete(ApplicationManager* pAppManager);

	// No parameters needed - operates on already selected item
	virtual void ReadActionParameters();

	// Execute the delete operation
	virtual void Execute();
};

#endif