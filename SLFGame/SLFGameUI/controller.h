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
    UI* m_pUi;
    Interactor* m_pInter;
};

#endif // CONTROLLER_H
