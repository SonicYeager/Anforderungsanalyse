#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "UI.h"
#include "Interactor.h"

class Controller
{
public:
    explicit Controller(UI*, Interactor*);
    void Run();
private:
    UI* p_ui;
    Interactor* p_inter;
};

#endif // CONTROLLER_H
