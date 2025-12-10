#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\DEFS.h"


//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)

	int width, height;	//Window width and height
	int wx, wy;			//Window starting coordinates

	int StatusBarHeight;	//Status Bar Width
	int ToolBarHeight;		//Tool Bar Width
	int MenuItemWidth;		//Menu Item Width
	int DrawingAreaWidth;   //Drawing Area Width

	color DrawColor;		//Drawing color
	color HighlightColor;		//Highlighting color
	color MsgColor;		//Messages color

	int ASSGN_WDTH;		//Assignment statement default width
	int ASSGN_HI;		//Assignment statement default height

	color ConnectorColor;      // ADD THIS
	


	// Conditional Statement size
	int COND_WDTH = 200;
	int COND_HI = 100;

	// Read Statement size
	int READ_WDTH = 150;
	int READ_HI = 80;

	// Write Statement size
	int WRITE_WDTH = 150;
	int WRITE_HI = 80;

	// Start/End Statement size
	int START_END_WDTH = 160;
	int START_END_HI = 80;



}UI;	//create a single global object UI

struct Point
{
	int x, y;
	Point(int a = 0, int b = 0)	//constructor
	{
		x = a;	y = b;
	}
};

#endif