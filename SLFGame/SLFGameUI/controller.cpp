#include "controller.h"
#include "DataTypes.h"

Controller::Controller(UI* ui, ClientInteractor* clientInter, ServerInteractor* serverInter) :
    m_pUi(ui),
    m_pServerInter(serverInter),
    m_pClientInter(clientInter)
{
    //connect ui + inter
    m_pUi->onPrepareGame                = [this](std::string customCats, std::string timeLeft, std::string maxRounds)
                                          {m_pClientInter->PrepareGame(customCats, timeLeft, maxRounds);};

    m_pUi->onPrepareOverview            = [this](Categories answers)
                                          {m_pClientInter->PrepareOverview(answers);};

    m_pUi->onPrepareNextRound           = [this](std::vector<DECISION> decisions)
                                          {m_pClientInter->EndRound(decisions);};

    m_pUi->onHostLobby                  = [this](const std::string& playerName)
                                          {m_pClientInter->HostLobby(playerName);};

    m_pUi->onJoinLobby                  = [this](const std::string& lobbyCode, const std::string& playerName)
                                          {m_pClientInter->JoinLobby(lobbyCode, playerName);};

    m_pClientInter->onReceivedID        = [this](int id)
                                          {m_pUi->ReceiveID(id);};

    m_pClientInter->onPrepareGame       = [this](GameStats gs)
                                          {m_pUi->PrepareGame(gs);};

    m_pClientInter->onPrepareOverview   = [this](GameStats gs)
                                          {m_pUi->PrepareOverview(gs);};

    m_pClientInter->onPrepareNextRound  = [this](GameStats gs)
                                          {m_pUi->PrepareGame(gs);};

    m_pClientInter->onGameOver          = [this](GameStats gs)
                                          {m_pUi->PrepareFinalScores(gs);};

    m_pClientInter->onPrepareLobby      = [this](GameStats gs)
                                          {m_pUi->PrepareLobby(gs);};

    m_pClientInter->onUpdateLobby       = [this](GameStats gs)
                                          {m_pUi->UpdateGameStats(gs);};

    m_pClientInter->onStartServer       = [this]()
                                          {m_pServerInter->StartServer();};

}

void Controller::Run()
{
    //init here
}
