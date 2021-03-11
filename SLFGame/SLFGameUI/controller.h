#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "UI.h"
#include "ClientInteractor.h"
#include "ServerInteractor.h"

class Controller
{
public:
    explicit Controller(UI*, ClientInteractor*, ServerInteractor*);
    void Run();
private:
    UI* m_pUi;
    ServerInteractor* m_pServerInter;
    ClientInteractor* m_pClientInter;
};

#endif // CONTROLLER_H
