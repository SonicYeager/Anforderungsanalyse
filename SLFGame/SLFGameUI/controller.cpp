#include "controller.h"
#include "DataTypes.h"

Controller::Controller(UI* ui, Interactor* inter) :
    p_ui(ui),
    p_inter(inter)
{
    //connect ui + inter
    p_ui->onPrepareGame = [this](std::string str1, std::string str2, std::string str3){p_inter->PrepareGame(str1, str2, str3);};
    p_inter->onPrepareNextRound = [this](GameStats gs, PlayerStats ps){p_ui->PrepareNextRound(gs,ps);};
}

void Controller::Run()
{
    //init here
    auto stats = p_inter->PrepareLobby("");
    p_ui->Init(stats.first, stats.second);
}
