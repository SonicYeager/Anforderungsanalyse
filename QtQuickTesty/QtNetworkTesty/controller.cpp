#include "controller.h"

controller::controller(QmlAdapter* oui, Interactor* inter, ServerInteractor* sinter) :
    ui(oui),
    interactor(inter),
    serverInteractor(sinter)
{
    //connect ui + inter | inter + inter
    ui->onJoinHost = [this](){ interactor->JoinHost();};
    ui->onStartHost = [this](){ interactor->StartHost();};
    interactor->onLog = [this](const std::string& data){ui->LogConnection(data);};
    interactor->onStartServer = [this](){serverInteractor->StartServer();};
    serverInteractor->onLog = [this](const std::string& data){ui->LogConnection(data);};
}

void controller::Run()
{
    //init here if any
}
