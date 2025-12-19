#ifndef CUT_H
#define CUT_H

#include "Action.h"

class Copy;
class Cut : public Action
{
public:
	Cut(ApplicationManager* pAppManager);
	virtual void ReadActionParameters() override {};
	// Execute the cut operation (copy + delete)
	virtual void Execute();
};

#endif