#include "controller.h"

controller::controller(QmlAdapter* oui, Interactor* inter, ServerInteractor* sinter) :
    ui(oui),
    interactor(inter),
    serverInteractor(sinter)
{
    //connect ui + inter | inter + inter
    ui->onJoinServer = [this](){ interactor->JoinServer();};
    ui->onStartServer = [this]()
        { interactor->StartServer();};
    ui->onSendData = [this](){ interactor->SendData();};
    interactor->onLog = [this](const std::string& data){ui->LogConnection(data);};
    interactor->onStartServer = [this]()
        {serverInteractor->StartServer();};
    serverInteractor->onLog = [this](const std::string& data){ui->LogConnection(data);};
}

void controller::Run()
{
    //init here if any
}
