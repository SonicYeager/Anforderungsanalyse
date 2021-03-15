#include "controller.h"
#include "DataTypes.h"

Controller::Controller(UI* ui, ClientInteractor* clientInter, ServerInteractor* serverInter) :
    m_pUi(ui),
    m_pServerInter(serverInter),
    m_pClientInter(clientInter)
{
    //UI EVENTS

    //m_pUi->onPrepareNextRound           = [this](std::vector<DECISION> decisions)
    //                                      {m_pClientInter->EndRound(decisions);};

    m_pUi->onHostLobby                  = [this](const std::string& playerName)
                                            {m_pClientInter->HostLobby(playerName);};

    m_pUi->onJoinLobby                  = [this](const std::string& lobbyCode, const std::string& playerName)
                                            {m_pClientInter->JoinLobby(lobbyCode, playerName);};

    m_pUi->onLobbySettingsChanged       = [this](const std::string& customCats,const std::string& timeLeft,const std::string& maxRounds)
                                            {m_pClientInter->LobbyChanged(customCats, timeLeft, maxRounds);};

    m_pUi->onChatMessage                = [this](const std::string& sender, const std::string& text)
                                            {m_pClientInter->ChatMessageReceived(sender,text);};

    m_pUi->onState                      = [this](const STATE& state)
                                            {m_pClientInter->StateChangeTriggered(state);};

    m_pUi->onSendAnswers                = [this](const std::vector<std::string> answers)
                                            {m_pClientInter->AnswersReceived(answers);};

    //CLIENT EVENTS

    m_pClientInter->onReceivedID            = [this](int id)
                                                {m_pUi->ReceiveID(id);};

    m_pClientInter->onUpdateLobbySettings   = [this](LobbySettings ls)
                                                {m_pUi->UpdateLobby(ls);};

    m_pClientInter->onStartServer           = [this]()
                                                {m_pServerInter->StartServer();};

    m_pClientInter->onSetLobbyCode          = [this](LobbyCode lobbyCode)
                                                {m_pUi->SetLobbyCode(lobbyCode);};

    m_pClientInter->onGameState             = [this](STATE state)
                                                {m_pUi->UpdateGameState(state);};

    m_pClientInter->onChatMessage           = [this](ChatMessage cm)
                                                {m_pUi->ChatMessageReceived(cm);};

    m_pClientInter->onCategories            = [this](std::vector<std::string> categories)
                                                {m_pUi->ReceiveCategories(categories);};

    m_pClientInter->onAllAnswers            = [this](std::vector<std::vector<std::string>> answers)
                                                {m_pUi->ReveiveAllAnswers(answers);};
}

void Controller::Run()
{
    //init here
}
