#include "controller.h"
#include "DataTypes.h"

Controller::Controller(UI* ui, Interactor* inter) :
    p_ui(ui),
    p_inter(inter)
{
    //connect ui + inter
}

void Controller::Run()
{
    //init here
    auto stats = p_inter->PrepareLobby("");
    p_ui->Init(stats.first, stats.second);
}
