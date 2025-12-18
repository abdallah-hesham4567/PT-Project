#include "ApplicationManager.h"
#include <windows.h>
//NOTE: YOU MUST NOT CHANGE THE MAIN FUNCTION

int main()
{
	FreeConsole(); // to hide the console window
	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;
	do
	{		
		//Step I - Read user input (action)
		ActType = AppManager.GetUserAction();

		//Steps II & III - Create & Exexute the action
		AppManager.ExecuteAction(ActType);

		//Step IV - Update the interface
		AppManager.UpdateInterface();	

	}while(ActType != EXIT);	
	return 0;
}

