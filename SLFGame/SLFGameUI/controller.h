#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "UI.h"
#include "GameInteractor.h"
#include "ClientInteractor.h"
#include "ServerInteractor.h"

#include <QObject>

class Controller
{
public:
    explicit Controller(UI*, GameInteractor* ,
    ClientInteractor* ,
    ServerInteractor* );
    int Run(int argc, char *argv[], QObject& obj);
private:
    GameInteractor* m_pGameInter;
    ClientInteractor* m_pClientInter;
    ServerInteractor* m_pServerInter;
    UI* m_pUi;
};

#endif // CONTROLLER_H
