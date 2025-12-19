#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H
#include "AddConnector.h"
#include "DEFS.h"
#include <fstream>
#include <map>
#include "Statements\Statement.h"
class Input;
class Output;


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)

	Statement* SelectedStatement; //a pointer to the last selected statement
	//you can set and get this pointer
	Statement* Clipboard;    //a pointer to the last copied/cut statement
	//you can set and get this pointer
	Connector* SelectedConnector;
//Pointers to Input and Output classes
	Input* pIn;
	Output* pOut;
	bool SelectionMode;

public:
	ApplicationManager();
	
	~ApplicationManager();

	// == Actions Related Functions ==
	ActionType GetUserAction() const; //Reads the input command from the user 
	//and returns the corresponding action type
	void ExecuteAction(ActionType);  //Creates an action and executes it

	// == Statements/Connector Management Functions ==
	
	//TODO: Complete its implementation 
	//      WITHOUT breaking class responsibilities

	void AddConnector(Connector* pConn);    //Adds a new Connector to the Flowchart
	void AddStatement(Statement* pStat);    //Adds a new Statement to the Flowchart
	
	
	Connector* GetConnectorAtPoint(Point p) const; //search for a Connector where point P belongs
	//Statement* GetStatementAtPoint(Point p) const; //search for a statement where point P belongs
	Statement* GetStatement(Point P) const;	//Searches for a statement where point P belongs


	int GetOutConnCount(Statement* pStat) const;
	int GetInConnCount(Statement* pStat) const;
	//Connector** GetOutConnectors(Statement* pStat, int& count) const;

	void DeleteStatement(Statement* statement); // Deletes a selected statement 
	void DeleteConnector(Connector* pConn);		// Deletes a selecetdd connector 
	void DeleteStatementConnectors(Statement* pStat);  // Deletes all connectors connected to a statement that is being deleted uses (DeleteConnector)


	//bool ValidateConnectors(string& errorMsg) const;
	Connector* GetSelectedConnector() {
		return SelectedConnector
			;
	} const
		void SetSelectedConnector(Connector* pConn) { SelectedConnector = pConn; }
	void UpdateAllConnectors();
;
	void SaveAll(ofstream& OutFile);





	// Note: you should use the following 4 functions 
	//       in order not to break class responsibilities (especially in copy, cut and paste)
	Statement* GetSelectedStatement() const;	 //Returns the selected Statement
	void SetSelectedStatement(Statement* pStat); //Set the Statement selected by the user

	Statement* GetClipboard() const;	         //Returns the Clipboard
	void SetClipboard(Statement* pStat);         //Set the Clipboard

	void UnselectAll();


	// == Interface Management Functions ==
	Input* GetInput() const;        //Return pointer to the input
	Output* GetOutput() const;      //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window


	// == Simulation Functions ==
	bool IsValid() const;
	Statement* GetNextStatement(Statement* pStat);
	Statement* GetNextAfterCondition(Statement* pStat,bool result);
	void RunSimulation();


	void LoadAll(ifstream& InFile);
	Statement* GetStatementWithID(int id) const;
	bool ApplicationManager::InDrawingArea(Point p, int w, int h) const
	{
		return (p.x >= 0 && p.x + w <= UI.DrawingAreaWidth && p.y >= UI.ToolBarHeight && p.y + h <= UI.height - UI.StatusBarHeight);
	}








	// Returns all output connectors from a statement
	// count will be set to the number of connectors found
	// Returns dynamically allocated array (caller must delete[])
	Connector** GetOutConnectors(Statement* pStat) const;



	// Returns all input connectors to a statement
	// count will be set to the number of connectors found
	// Returns dynamically allocated array (caller must delete[])
	Connector** GetInConnectors(Statement* pStat, int& count) const;
	int GetUsedBranch(Statement* src);
	void SetSelectionMode(bool m) { SelectionMode = m; }
	bool IsSelectionModeOn() const { return SelectionMode; }
	bool CanPlaceStatement(Point p, int w, int h) const;
	void ClearAll(); // Clear all statements and connectors


	void RunStartup();

};

#endif