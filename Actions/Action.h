#ifndef ACTION_H
#define ACTION_H

//#include "CMUgraphicsLib\CMUgraphics.h"
class ApplicationManager; //forward class declaration
class Input;
class Output;

#include "..\GUI\UI_Info.h"


//Base class for all possible actions
class Action
{
protected:
	
	//Pointer to ApplicationManager because action needs this pointer for its functions
	ApplicationManager *pManager;	

public:

	Action(ApplicationManager *pAppManager) 
	{ pManager = pAppManager; }
	
	//Reads parameters required for action to execute
	virtual void ReadActionParameters() =0;
	
	//Execute action (code depends on action type)
	virtual void Execute() =0;

	//cheking if the point is in the drawing area
	virtual bool InDrawingArea(Point P) const
	{
		return (P.y >= UI.ToolBarHeight+UI.COND_HI && P.y < UI.height - UI.StatusBarHeight-UI.COND_HI && P.x >= UI.COND_WDTH && P.x <= UI.DrawingAreaWidth-UI.COND_WDTH);
	}
};

#endif