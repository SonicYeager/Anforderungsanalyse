#include "controller.h"
#include "DataTypes.h"

Controller::Controller(UI* ui, Interactor* inter) :
    m_pUi(ui),
    m_pInter(inter)
{
    //connect ui + inter
    m_pUi->onPrepareGame         = [this](std::string customCats, std::string timeLeft, std::string maxRounds)
                                    {m_pInter->PrepareGame(customCats, timeLeft, maxRounds);};

    m_pUi->onPrepareOverview     = [this](Categories answers, int id)
                                    {m_pInter->PrepareOverview(answers, id);};

    m_pUi->onPrepareNextRound    = [this](std::vector<DECISION> decisions, int id)
                                    {m_pInter->EndRound(decisions, id);};

    m_pUi->onHost                = [this]()
                                    {m_pInter->HostGame("Placebo");};

    m_pUi->onJoin                = [this](const std::string& lobbyCode)
                                    {m_pInter->JoinGame(lobbyCode, "PlaceboClient");};

    m_pInter->onPrepareGame =      [this](GameStats gs)
                                    {m_pUi->PrepareGame(gs);};

    m_pInter->onPrepareOverview  = [this](GameStats gs)
                                    {m_pUi->PrepareOverview(gs);};

    m_pInter->onPrepareNextRound = [this](GameStats gs)
                                    {m_pUi->PrepareGame(gs);};

    m_pInter->onGameOver         = [this](GameStats gs)
                                    {m_pUi->PrepareFinalScores(gs);};

    m_pInter->onGameHosted       = [this](GameStats gs)
                                    {m_pUi->PrepareLobby(gs);};

    m_pInter->onGameJoined       = [this](GameStats gs)
                                    {m_pUi->PrepareLobby(gs);};

    m_pInter->onNewPlayerJoined  = [this](GameStats gs, int id)
                                    {m_pUi->PlayerJoined(gs, id);};

}

void Controller::Run()
{
    //init here
}
