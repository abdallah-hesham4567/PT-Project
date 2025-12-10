#ifndef STATEMENT_H
#define STATEMENT_H
#include <string>
#include <fstream>
#include "..\defs.h"
#include "..\Connector.h"
//class Output;
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"
//Base class for all Statements
class Statement
{
protected:
	int ID;			//Each Statement has an ID --> must be unique
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart
	static int NextID;
	Connector* pOutconn;

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:
	Statement();
	

	

    // Get outlet point for connectors (branch: 0=default, 1=YES, 2=NO)
    virtual Point GetOutletPoint(int branch = 0) const = 0;

    // Get inlet point for connectors
    virtual Point GetInletPoint() const = 0;

    // Get expected number of output connectors
	virtual int GetExpectedOutConnCount() const = 0;

    // Check if this is a conditional statement
    virtual bool IsConditional() const { return false; }

    // Check if point is inside statement (for selection)
    virtual bool IsPointInside(Point p) const = 0;

	// 
	//virtual void SetPosition(Point &p){}

    // Existing virtual methods
	virtual void Draw(Output* pOut) const = 0; 
	virtual void Save(ofstream& OutFile) const =0;
    virtual void Load(ifstream& InFile) = 0;

    // Getters/Setters
	void setID(int id) { ID = id; }
    int GetID() const { return ID; }
    void SetSelected(bool s) { Selected = s; }
    bool IsSelected() const { return Selected; }


	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type


	virtual void Edit() = 0;		//Edit the Statement parameter
	virtual string getStatementType() const = 0;
	//virtual void Simulate();	//Execute the statement in the simulation mode

	// virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file


	///TODO: Add more functions if needed

	virtual void SetOutConn(Connector* pConn);
	Connector* GetOutConn();  //return the outgoing connector for the statement
	
	

	int GetIncomingCount();   // Get the number of incoming connectors
	 
	Connector* GetIncomingConnector(int index);//returns a specific incoming connector given it's index
	virtual Statement* Clone() const =0 ;

};

#endif