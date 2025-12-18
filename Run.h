#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
class Run :public Action
{
	public:
	Run(ApplicationManager* pAppManager):Action(pAppManager){};
	virtual void ReadActionParameters();
	virtual void Execute();
};

