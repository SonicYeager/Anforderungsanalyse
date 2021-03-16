#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "UI.h"
#include "GameInteractor.h"

class Controller
{
public:
    explicit Controller(UI*, GameInteractor*);
    void Run();
private:
    UI* m_pUi;
    GameInteractor* m_pClientInter;
};

#endif // CONTROLLER_H
