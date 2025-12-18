#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters

	UI.width = 2000;
	UI.height = 800;
	UI.wx = 15;
	UI.wy = 15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode
	UI.StatusBarHeight = 100;
	UI.ToolBarHeight = 70;
	UI.MenuItemWidth = 67;

	UI.DrawingAreaWidth = .60 * UI.width;
	UI.DrawColor = BLUE;                    // color for normal shapes
	UI.HighlightColor = YELLOW;            // color for highlighted shapes
	UI.MsgColor = BLACK;                  // color for messages

	UI.ASSGN_WDTH = 200;                 // width rectangle 
	UI.ASSGN_HI = 45;                    // hight rectangle 

	UI.COND_WDTH = 160;                  // width diamond
	UI.COND_HI = 100;                    // hight diamond

	UI.READ_WDTH = 160;                  // width Parallelogram
	UI.READ_HI = 80;                     // hight Parallelogram

	UI.WRITE_WDTH = 160;                 // width Parallelogram
	UI.WRITE_HI = 80;                    // hight Parallelogram

	UI.START_END_WDTH = 160;             // width ellipse 
	UI.START_END_HI = 60;                // hight ellipse

	UI.ConnectorColor = BLACK;
	UI.HighlightColor = RED;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, 0, 0);


	pWind->ChangeTitle("CodeFlow");      //app Title 



	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}


void Output::CreateStatusBar()           // to create status bar
{
	//Draw a line above  the statusbar
	pWind->SetPen(RED, 2);

	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}


void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode

	// the coming is the images for icons in order
	string MenuItemImages[DSN_ITM_CNT];
	MenuItemImages[ITM_START] = "images\\start.jpg";
	MenuItemImages[ITM_END] = "images\\end.jpg";
	MenuItemImages[ITM_DECLARE_VARIABLE] = "images\\declare variable.jpg";
	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\value assign.jpg";
	MenuItemImages[ITM_VAR_ASSIGN] = "images\\variable assign.jpg";
	MenuItemImages[ITM_OPER_ASSIGN] = "images\\op assign.jpg";
	MenuItemImages[ITM_READ] = "images\\read.jpg";
	MenuItemImages[ITM_WRITE] = "images\\write.jpg";
	MenuItemImages[ITM_COND] = "images\\condition.jpg";
	MenuItemImages[ITM_LOOP] = "images\\loop.jpg";
	MenuItemImages[ITM_CONNECTOR] = "images\\connector.jpg";
	MenuItemImages[ITM_DELETE] = "images\\delete.jpg";
	MenuItemImages[ITM_COPY] = "images\\copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\paste.jpg";
	MenuItemImages[ITM_SELECT] = "images\\select.jpg";
	MenuItemImages[ITM_EDIT] = "images\\edit.jpg";
	MenuItemImages[ITM_SAVE] = "images\\save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\load.jpg";
	MenuItemImages[ITM_SWITCH_SIM] = "images\\simulation mode.jpg";
	MenuItemImages[ITM_UNDO] = "images\\undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\redo.jpg";
	MenuItemImages[ITM_EXIT] = "images\\exit.jpg";


	//Draw menu item one image at a time
	int index = 0;
	for (index; index < DSN_ITM_CNT; index++)
	{
		pWind->DrawImage(MenuItemImages[index], index * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}


	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}


void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	// the coming is the images for icons in order

	string MenuItemImages[SIM_ITM_CNT];
	MenuItemImages[ITM_VALIDATE] = "images\\validity.jpg";
	MenuItemImages[ITM_RUN] = "images\\run.jpg";
	MenuItemImages[ITM_CPP] = "images\\c++.jpg";
	MenuItemImages[ITM_EXITS] = "images\\exit.jpg";
	MenuItemImages[ITM_SWITCH_DSN] = "images\\design mode.jpg";



	//Draw menu item one image at a time


	for (int i = 0; i < SIM_ITM_CNT; i++)
	{
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}

	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

//clear DESIGN toolbar

void Output::Clear_DesignToolBar()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);

	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}


//clear SIMULATION toolbar

void Output::Clear_SimulationToolBar()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);

	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

// to clear status bar 
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(YELLOW);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

// to clear Drawing area
void Output::ClearDrawArea()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}

// to clear Output area
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(GREY);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}


//Prints a message on status bar
void Output::PrintMessage(string msg)
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Roboto");     //WAS ARIAL   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}


//To draw a message
void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}



//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

// draw rectangle

void Output::DrawAssignAndDeclare(Point Left, int width, int height, string Text, bool Selected)
{
	//  check if selected or not to choose it will normal or highligted 

	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);  // highlighted
	else
		pWind->SetPen(UI.DrawColor, 3);       // normal

	//  check if   Empty / Filled
	if (Text.empty())
		pWind->SetBrush(BLUE);               // empty
	else
		pWind->SetBrush(WHITE);             // filled

	// to draw rectangle it takes the left-up point and right-down point

	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);

	// to put string into the shape and we will modify it in phase 2 two change based on the long of the word 

	if (!Text.empty())
	{
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(Left.x + 10, Left.y + 10, Text);
	}
}

//draw ellipse 
// all shapes are similar in most of construcion

void Output::DrawStart(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	if (Text.empty())
		pWind->SetBrush(BLUE);
	else
		pWind->SetBrush(WHITE);

	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height);


	if (!Text.empty())
	{
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
	}
}

// also draws ellipse and does the same function but it was written in TODO

void Output::DrawEnd(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	if (Text.empty())
		pWind->SetBrush(BLUE);
	else
		pWind->SetBrush(WHITE);

	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height);

	if (!Text.empty())
	{
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
	}
}

// draw conditional  statment as diamond shape 

void Output::DrawConditionalStat(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	if (Text.empty())
		pWind->SetBrush(BLUE);
	else
		pWind->SetBrush(WHITE);

	// it takes 4 point start from the top point and rotate clock wise

	int x[4] = { Left.x + width / 2, Left.x + width, Left.x + width / 2, Left.x };
	int y[4] = { Left.y, Left.y + height / 2, Left.y + height, Left.y + height / 2 };

	pWind->DrawPolygon(x, y, 4);

	if (!Text.empty())
	{
		pWind->SetPen(BLACK, 2);
		// maybe the size not perfect but it doesnot require in this phase so we modify also later
		pWind->DrawString(Left.x + 30, Left.y + height / 3, Text);
	}
}

// draw read or write statment as Parallelogram 
void Output::DrawReadAndWrite(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	if (Text.empty())
		pWind->SetBrush(BLUE);
	else
		pWind->SetBrush(WHITE);

	//it takes 4 points start from the left _up and rotate clock wise similar to diamond 

	int x[4] = { Left.x + 20, Left.x + width, Left.x + width - 20, Left.x };
	int y[4] = { Left.y, Left.y, Left.y + height, Left.y + height };

	// Draw the parallelogram
	pWind->DrawPolygon(x, y, 4);

	if (!Text.empty())
	{
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
	}
}

// draw connector

void Output::DrawConnector(Point Start, Point End, bool Selected)
{
	if (Selected)               // if highlighted
		pWind->SetPen(UI.HighlightColor, 3);
	else                             // if normal
		pWind->SetPen(UI.DrawColor, 2);

	pWind->DrawLine(Start.x, Start.y, End.x, End.y);


	// to draw Arrow 
	double angle = atan2(End.y - Start.y, End.x - Start.x);
	double len = 12, s = 0.45;

	pWind->DrawLine(End.x, End.y, End.x - len * cos(angle - s), End.y - len * sin(angle - s));
	pWind->DrawLine(End.x, End.y, End.x - len * cos(angle + s), End.y - len * sin(angle + s));
}

void Output::DrawMidPoint(Point Start, Point End, bool Selected)
{
	if (Selected)               // if highlighted
		pWind->SetPen(UI.HighlightColor, 3);
	else                             // if normal
		pWind->SetPen(UI.DrawColor, 2);

	pWind->DrawLine(Start.x, Start.y, End.x, End.y);

}
void Output::PrintOutput(const string& text)
{
	if (OutputY == 0)
		OutputY = UI.ToolBarHeight + 20;

	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20, BOLD, BY_NAME, "Roboto");

	pWind->DrawString(
		UI.DrawingAreaWidth + 20,
		OutputY,
		text
	);

	OutputY += 25; 
}


//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}
