#include "controller.h"

controller::controller(QmlAdapter* oui, Interactor* inter) :
    ui(oui),
    interactor(inter)
{
    //connect ui + inter
    ui->onJoinHost = [this](){ interactor->JoinHost();};
    ui->onStartHost = [this](){ interactor->StartHost();};
    interactor->onDataReceived = [this](const std::string& data){ui->LogConnection(data);};
    interactor->onNewConnection = [this](const std::string& data){ui->LogConnection(data);};
}

void controller::Run()
{
    //init here if any
}
