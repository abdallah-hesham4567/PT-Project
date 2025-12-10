#ifndef DELETE_H
#define DELETE_H

#include "Action.h"

class ApplicationManager;
class Statement;
class Connector;

// Delete action - deletes the currently selected statement or connector
class Delete : public Action {
private:

public:
    Delete(ApplicationManager* pAppManager);

    // Execute the delete action
    virtual void Execute();

    // Undo the delete action (optional - for undo/redo support)
    //virtual void Undo();
};

#endif