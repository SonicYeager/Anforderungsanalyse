#include "controller.h"
#include "DataTypes.h"

Controller::Controller(UI* ui, Interactor* inter) :
    m_pUi(ui),
    m_pInter(inter)
{
    //connect ui + inter
    m_pUi->onPrepareGame         = [this](std::string customCats, std::string timeLeft, std::string maxRounds)
                                    {m_pInter->PrepareGame(customCats, timeLeft, maxRounds);};

    m_pUi->onPrepareOverview     = [this](Categories answers)
                                    {m_pInter->PrepareOverview(answers);}
    ;
    m_pUi->onPrepareNextRound    = [this](std::vector<int> decisions)
                                    {m_pInter->EndRound(decisions);};

    m_pInter->onPrepareGame =      [this](GameStats gs, PlayerStats ps)
                                    {m_pUi->PrepareGame(gs,ps);};

    m_pInter->onPrepareOverview  = [this](GameStats gs, PlayerStats ps)
                                    {m_pUi->PrepareOverview(gs,ps);};

    m_pInter->onPrepareNextRound = [this](GameStats gs, PlayerStats ps)
                                    {m_pUi->PrepareGame(gs,ps);};

    m_pInter->onGameOver         = [this](GameStats gs, PlayerStats ps)
                                    {m_pUi->PrepareFinalScores(gs,ps);};

}

void Controller::Run()
{
    //init here
    auto stats = m_pInter->PrepareLobby("");
    m_pUi->Init(stats.first, stats.second);
}
