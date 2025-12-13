//#include "ActionLoad.h"
//#include "..\ApplicationManager.h"
//#include "..\GUI\Input.h"
//#include "..\GUI\Output.h"
//
//// Include all statement types for dynamic creation
//#include "..\Start.h"
//#include "..\End.h"
//#include "..\Statements\ValueAssign.h"
//#include "..\VariableAssign.h"
//#include "..\OperatorAssignment.h"
//#include "..\ConditionStatement.h"
//#include "..\Read.h"
//#include "..\Write.h"
//#include "..\DeclareStatement.h"
//#include "..\Connector.h"
//
//#include <fstream>
//
//ActionLoad::ActionLoad(ApplicationManager* pAppManager) : Action(pAppManager)
//{
//}
//
//void ActionLoad::ReadActionParameters()
//{
//    // Get pointer to the input and output interfaces
//    Output* pOut = pManager->GetOutput();
//    Input* pIn = pManager->GetInput();
//
//    // Print message asking user to enter filename
//    pOut->PrintMessage("Load Flowchart: Enter filename to load");
//
//    // Read filename from user
//    FileName = pIn->GetString(pOut);
//
//    // Clear status bar
//    pOut->ClearStatusBar();
//}
//
//void ActionLoad::Execute()
//{
//    // Read action parameters (filename)
//    ReadActionParameters();
//
//    // Open the input file
//    ifstream InFile(FileName + ".txt");
//
//    if (!InFile.is_open())
//    {
//        Output* pOut = pManager->GetOutput();
//        pOut->PrintMessage("Error: Cannot open file for loading!");
//        return;
//    }
//
//    // Clear the current drawing area (cleanup existing flowchart)
//    pManager->ClearAll();
//
//    // Read number of statements
//    int StatCount;
//    InFile >> StatCount;
//
//    // Loop to read all statements
//    for (int i = 0; i < StatCount; i++)
//    {
//        string StatType;
//        InFile >> StatType;
//
//        Statement* pStat = nullptr;
//
//        // Create appropriate statement based on type
//        if (StatType == "STRT")
//            pStat = new Start();
//        else if (StatType == "END")
//            pStat = new End();
//        else if (StatType == "DECLARE")
//            pStat = new Declare();
//        else if (StatType == "VALUE_ASSIGN")
//            pStat = new ValueAssign();
//        else if (StatType == "VAR_ASSIGN")
//            pStat = new VarAssign();
//        else if (StatType == "OP_ASSIGN")
//            pStat = new OperatorAssign();
//        else if (StatType == "COND")
//            pStat = new Conditional();
//        else if (StatType == "READ")
//            pStat = new Read();
//        else if (StatType == "WRITE")
//            pStat = new Write();
//
//        if (pStat)
//        {
//            // Call the Load function of the statement to read its data
//            pStat->Load(InFile);
//
//            // Add the statement to the ApplicationManager
//            pManager->AddStatement(pStat);
//        }
//    }
//
//    // Read number of connectors
//    int ConnCount;
//    InFile >> ConnCount;
//
//    // Loop to read all connectors
//    for (int i = 0; i < ConnCount; i++)
//    {
//        int SrcID, DstID, OutletBranch;
//        InFile >> SrcID >> DstID >> OutletBranch;
//
//        // Get pointers to source and destination statements
//        Statement* pSrc = pManager->GetStatement(SrcID);
//        Statement* pDst = pManager->GetStatement(DstID);
//
//        if (pSrc && pDst)
//        {
//            // Create connector
//            Connector* pConn = new Connector(pSrc, pDst);
//
//            // Set outlet branch if applicable (for conditional statements)
//            if (OutletBranch != 0)
//                pConn->setOutletBranch(OutletBranch);
//
//            // Add connector to ApplicationManager
//            pManager->AddConnector(pConn);
//        }
//    }
//
//    // Close the file
//    InFile.close();
//
//    // Print success message
//    Output* pOut = pManager->GetOutput();
//    pOut->PrintMessage("Flowchart loaded successfully from " + FileName + ".txt");
//}