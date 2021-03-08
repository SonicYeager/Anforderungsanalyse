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
                                    {m_pInter->PrepareOverview(answers);};

    m_pUi->onPrepareNextRound    = [this](std::vector<DECISION> decisions)
                                    {m_pInter->EndRound(decisions);};

    m_pUi->onHostLobby            = [this](const std::string& playerName)
                                    {m_pInter->HostLobby(playerName);};

    m_pUi->onJoinLobby            = [this](const std::string& lobbyCode, const std::string& playerName)
                                    {m_pInter->JoinLobby(lobbyCode, playerName);};

    m_pInter->onPrepareGame =      [this](GameStats gs)
                                    {m_pUi->PrepareGame(gs);};

    m_pInter->onPrepareOverview  = [this](GameStats gs)
                                    {m_pUi->PrepareOverview(gs);};

    m_pInter->onPrepareNextRound = [this](GameStats gs)
                                    {m_pUi->PrepareGame(gs);};

    m_pInter->onGameOver         = [this](GameStats gs)
                                    {m_pUi->PrepareFinalScores(gs);};

    m_pInter->onPrepareLobby      = [this](GameStats gs)
                                    {m_pUi->PrepareLobby(gs);};

    m_pInter->onUpdateLobby       = [this](GameStats gs)
                                    {m_pUi->UpdateGameStats(gs);};

}

void Controller::Run()
{
    //init here
}
