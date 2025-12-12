#include<string>
#include<iostream>
#include "Input.h"
#include "Output.h"
using namespace std;

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point& P) const
{
	pWind->WaitMouseClick(P.x, P.y); 	//Wait for mouse click
}

void Input::GoNext(Point& P)
{
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 13)   // ENTER
		{
			P.x = 0;
			P.y = 0;
			return;
		}
	}
}



///////////////



////////////

string Input::GetString(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}


double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{
	///TODO: add code to read a double value from the user and assign it to D

	double D = 0;

	pO->PrintMessage("Please enter a value");              //prompt user to enter a value

	string s = GetString(pO);

	while (!IsValue(s))		//asks user for a valid input 
	{
		pO->PrintMessage("Please enter a value");
		s = GetString(pO);
	}
	D = stod(s);				//convert string to double
	return D;                   // return a valid value and assigns it to D
}


//TODO: Add the function Input::GetVariable 
// to read a  variable name  from the user (from the keyboard). 
// It does not return before taking a valid variable name.

string Input::GetVariable(Output* pO) const
{
	pO->PrintMessage("Please enter a variable name");        //prompt user to enter a variable name
	string Variable = GetString(pO);
	while (!IsVariable(Variable))                            //asks user for a valid input
	{
		pO->PrintMessage("Please enter a true variable name");
		Variable = GetString(pO);
	}
	return Variable;                                        //return a valid variable name
}
string Input::GetVariableOrVal(Output* pO) const
{
	pO->PrintMessage("Please enter a variable name or a value");        //prompt user to enter a variable name or a value
	string VarOrVal = GetString(pO);
	while (!(IsVariable(VarOrVal) || IsValue(VarOrVal)))            //asks user for a valid input
	{
		pO->PrintMessage("Please enter a variable name or a value");
		VarOrVal = GetString(pO);
	}
	return VarOrVal;                                        //return a valid variable name or a value
}

//TODO: Add the function Input::GetArithOperator
// to read an arithmetic operator (+, -, * or /) from the user.
// It does not return before taking a valid arithmetic operator.

char Input::GetArithOperator(Output* pO) const
{
	pO->PrintMessage("Enter Arithmetic Operator:");          // prompt user to enter an arithmetic operator
	string Operator = GetString(pO);

	while (!(Operator == "+" || Operator == "-" || Operator == "*" || Operator == "/"))        //validate user input	
	{
		pO->PrintMessage("Enter Arithmetic Operator:");
		Operator = GetString(pO);
	}
	return char(Operator[0]);                                                  //return a valid arithmetic operator
}

//TODO: Add the function Input::GetCompOperator
// similar to the previous function but for comparison operators (==, !=, <, <=, > or >=).

string Input::GetCompOperator(Output* pO) const
{
	pO->PrintMessage("Enter Comparison Operator");                                  // prompt user to enter a comparison operator
	string CompOperator = GetString(pO);
	while (!(CompOperator == ">" || CompOperator == "<" || CompOperator == ">=" || CompOperator == "<=" || CompOperator == "==" || CompOperator == "!="))		//validate user input	
	{
		pO->PrintMessage("Enter Comparison Operator");
		CompOperator = GetString(pO);
	}
	return CompOperator;                                //return a valid comparison operator
}



//TODO: Complete the implementation of the following function
ActionType Input::GetUserAction() const
{
	//This function reads the position where the user clicks to determine the desired action

	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)                                             // return suitable action type for the button clicked depending on the coordinates of the click 
			{
			case ITM_START:                   return ADD_START;              //start statement 
			case ITM_END:                     return ADD_END;                 // end statement  
			case ITM_DECLARE_VARIABLE:        return ADD_DECLARE_VARIABLE;     //intiate a variable
			case ITM_VALUE_ASSIGN:            return ADD_VALUE_ASSIGN;         // assign a value to a variable
			case ITM_VAR_ASSIGN:              return ADD_VAR_ASSIGN;           // assign a variable to another variable
			case ITM_OPER_ASSIGN:             return ADD_OPER_ASSIGN;          // assign an arithmetic operation to a variable
			case ITM_READ:					  return ADD_READ;           //read variable 
			case ITM_WRITE:					  return ADD_WRITE;          //print the variable 
			case ITM_COND:					  return ADD_CONDITION;      // if condition 
			case ITM_LOOP:					  return ADD_LOOP;       // loop
			case ITM_CONNECTOR:				  return ADD_CONNECTOR;        //connector 
			case ITM_DELETE:				  return DEL;              // delete 
			case ITM_COPY:					  return COPY;             // copy
			case ITM_CUT:					  return CUT;              // cut
			case ITM_PASTE:					  return PASTE;            // paste
			case ITM_SELECT:				  return SELECT;           // select 
			case ITM_EDIT:					  return EDIT_STAT;            // edit selected 
			case ITM_SAVE:					  return SAVE;                  // save
			case ITM_LOAD:					  return LOAD;                  // restore 
			case ITM_REDO:					  return REDO;                  // redo last step 
			case ITM_UNDO:					  return UNDO;                  // undo last step 
			case ITM_SWITCH_SIM:			  return SWITCH_SIM_MODE;     //Switch to Simulation mode
			case ITM_EXIT:					  return EXIT;				  // Exit Application
			default:						  return DSN_TOOL;			  // A click on empty area in toolbar
			}

		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;
			else
				return OUTPUT_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;           // then user clicked on the status bar
	}

	else	//Application is in Simulation mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)             //user clicks on the Toolbar
		{
			int ClickedItem = (x / UI.MenuItemWidth);   // knows what is the number of the item clicked
			switch (ClickedItem)                        // return suitable action type for the button clicked depending on the position of the click relative to the item
			{
			case ITM_VALIDATE:      return VALIDATE;           //check the validity of the drawn flowchart
			case ITM_RUN:           return RUN;                //run the simulation
			case ITM_SWITCH_DSN:    return SWITCH_DSN_MODE;    //switch to Design mode
			case ITM_CPP:           return CPP;                //convert to C++ code
			case ITM_EXITS:         return EXIT;               //exit the application

			default:                return SIM_TOOL;           // A click on empty area in toolbar
			}
		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;
			else
				return OUTPUT_AREA;
		}

	}

}

Input::~Input()
{
}