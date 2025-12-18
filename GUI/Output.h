#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"
static int OutputY = 0;

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();

	window* CreateWind(int, int, int, int);
	Input* CreateInput(); //Creates a pointer to the Input object	

	void CreateStatusBar(); //Creates status bar

	//TODO: Complete the following 2 functions
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar(); //Tool bar of the simulation mode

	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area
	void ClearOutputBar(); //Clears the Output bar
	void Clear_DesignToolBar(); //clears the design toolbar
	void Clear_SimulationToolBar(); //clears the simulation toolbar

	void PrintMessage(string msg);	//Prints a message on Status bar
	void DrawString(const int, const int, const string);  //Writes a string in the specified location

	// -- Statements Drawing Functions

	void DrawStart(Point Left, int width, int height, string Text, bool Selected = false);          //draw ellipse
	void DrawEnd(Point Left, int width, int height, string Text, bool Selected = false);            // also draw ellipse but it is mentioned in todo so we repeat
	void DrawAssignAndDeclare(Point Left, int width, int height, string Text, bool Selected = false); //draw Rectangle
	void DrawConditionalStat(Point Left, int width, int height, string Text, bool Selected = false);      //draw diamond
	void DrawReadAndWrite(Point Left, int width, int height, string Text, bool Selected = false);      // draw  parallelogram
	void DrawConnector(Point Start, Point End, bool Selected = false);                                  //draw connector

	void PrintOutput(const string& text);


	//TODO: Add similar functions for drawing all other statements.
	//		e.g. DrawDeclareStat(.....), DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
	//		Decide the parameters that should be passed to each of them

	//TODO: Add DrawConnector function

	~Output();
};

#endif