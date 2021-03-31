#include "QmlAdapter.h"

QmlAdapter::QmlAdapter(QObject *parent) :
    QObject(parent)
{}

// ------------------------------------------ initializer function ------------------------------------------

void QmlAdapter::ReceiveID(int id)
{
    setPlayerId(id);
}

void QmlAdapter::UpdateLobby(const LobbySettings & ls)
{
    _customCategories = ls.categories.c_str();
    _maxRounds = ls.rounds.c_str();
    _roundTime = ls.timeout.c_str();
    _players.clear();
    _players = ls.playerNames;
    setPlayerCount(static_cast<int>(_players.size()));
    emit playerCountChanged();
    emit playersChanged();
    emit customCategoriesChanged();
    emit maxRoundsChanged();
    emit roundTimeChanged();
}

void QmlAdapter::SetLobbyCode(const LobbyCode & lobbycode)
{
    setLobbyCode(lobbycode.c_str());
}

void QmlAdapter::UpdateGameState(const STATE & state)
{
    setView(GetViewFromState(state));
    triggerStateRelatedSignal(state);
    clearChat();
}

void QmlAdapter::ChatMessageReceived(const ChatMessage & cm)
{
    AddChatMessage(cm.sender.c_str(), cm.text.c_str());
}

void QmlAdapter::ReveiveAllAnswers(const StrVector2D & answers)
{
    setAnswers(answers);
}

void QmlAdapter::ReceiveRoundData(const RoundData & data)
{
    setCategories(data.categories);
    setLetter(data.letter.c_str());
    setRoundTime(data.roundTime.c_str());
    setCurrentRound(data.currentRound);
    setMaxRounds(QString::number(data.maxRounds));
    setPoints(data.points);
}

void QmlAdapter::ReceiveVoteChange(const Index & index)
{
    setDecision(index.categoryIDX, index.answerIDX, index.voterIDX);
}

void QmlAdapter::ReceiveFinalScores(const Scores & scores)
{
    setScores(scores);
    setView(GetViewFromState(STATE::FINALSCORES));
}

void QmlAdapter::Disconnected()
{
    setView(GetViewFromState(STATE::MAINMENU));
    if (!_disconnectedByClient)
    {
        _disconnectedByClient = !_disconnectedByClient;
        emit disconnectedFromServer();
    }
}

void QmlAdapter::PlayerLeft(int id)
{
    QString msg = _players[id].c_str();
    AddChatMessage("*Server", msg + " hat das Spiel verlassen.");
    _players.erase(id);
    setPlayerCount(static_cast<int>(_players.size()));
    emit playerCountChanged();
    emit playersChanged();
}

// ------------------------------------------ getter ------------------------------------------
#define getterFunctions {

QString QmlAdapter::getLetter()
{
    return _letter;
}

QString QmlAdapter::getLobbyCode()
{
    return _lobbyCode;
}

QString QmlAdapter::getCustomCategories()
{
    return _customCategories;
}

StrVector QmlAdapter::getCategories()
{
    return _categories;
}

StrVector2D QmlAdapter::getAnswers()
{
    return _answers;
}

QList<QVariantMap> QmlAdapter::getPlayers()
{
   QList<QVariantMap> res{};
   for(const auto& player : _players)
       res.append(QVariantMap({{"id", QVariant(player.first)}, {"name", QVariant(QString(player.second.c_str()))}}));
    return res;
}

//bool QmlAdapter::getCustomChecked()
//{
//    return _customChecked;
//}

int QmlAdapter::getCategoryCount()
{
    return _categoryCount;
}

int QmlAdapter::getCurrentRound()
{
    return _currentRound;
}

QString QmlAdapter::getMaxRounds()
{
    return _maxRounds;
}

QString QmlAdapter::getRoundTime()
{
    return _roundTime;
}

int QmlAdapter::getPoints()
{
    return _points;
}

int QmlAdapter::getActiveOverviewItem()
{
    return _activeOverviewItem;
}

int QmlAdapter::getPlayerCount()
{
    return _playerCount;
}

int QmlAdapter::getPlayerId()
{
    return _playerId;
}

QString QmlAdapter::getTimeLeft()
{
    return _timeLeft;
}

QString QmlAdapter::getView()
{
    return _view;
}

QString QmlAdapter::getPlayerName()
{
    return _playerName;
}

QString QmlAdapter::getChatLog()
{
    return _chatLog;
}

#define getterFunctionsEnd }
// ------------------------------------------ setter ------------------------------------------
#define setterFuntions {

void QmlAdapter::setLetter(QString letter)
{
    if (letter == _letter)
        return;
    _letter = letter;
    emit letterChanged();
}

void QmlAdapter::setLobbyCode(QString lobbyCode)
{
    if (lobbyCode == _lobbyCode)
        return;
    _lobbyCode = lobbyCode;
    emit lobbyCodeChanged();
}

void QmlAdapter::setCustomCategories(QString customCategories)
{
    if (customCategories == _customCategories)
        return;
    _customCategories = customCategories;
    if(_playerId == 0)
        lobbySettingsChanged();
    emit customCategoriesChanged();
}

void QmlAdapter::setRoundTime(QString roundTime)
{
    if (roundTime == _roundTime)
        return;
    _roundTime = roundTime;
    if(_playerId == 0)
        lobbySettingsChanged();
    emit roundTimeChanged();
}

void QmlAdapter::setCategories(StrVector categories)
{
    if (categories == _categories)
        return;
    _categories = categories;
    _categoryCount = static_cast<int>(_categories.size());
    emit categoriesChanged();
    emit categoryCountChanged();
}

void QmlAdapter::setAnswers(StrVector2D answers)
{
    _answers = answers;
    _decisions.clear();
    for (int i = 0; i < _categoryCount; i++)
    {
        _decisions.emplace_back();
        for (int j = 0; j < _playerCount; j++)
        {
            _decisions[i].emplace_back();
            for (int k = 0; k < _playerCount; k++)
            {
                if(_answers[j][i] == "")
                    _decisions[i][j].emplace_back(false);
                else
                    _decisions[i][j].emplace_back(true);
            }
        }
    }
    emit answersChanged();
    emit decisionsChanged();
}

void QmlAdapter::setPlayers(QList<QVariantMap> players)
{
    PlayerMap res{};
    for(const auto& player : players)
        res.emplace(player["id"].toInt(), player["name"].toString().toStdString());
    if (res == _players)
        return;
    _players = res;
    emit playersChanged();
}

//void QmlAdapter::setCustomChecked(bool checked)
//{
//    if (checked == _customChecked)
//        return;
//    _customChecked = checked;
//    emit customCheckedChanged();
//}

void QmlAdapter::setCategoryCount(int categoryCount)
{
    if (categoryCount == _categoryCount)
        return;
    _categoryCount = categoryCount;
    emit categoryCountChanged();
}

void QmlAdapter::setCurrentRound(int currentRound)
{
    if (currentRound == _currentRound)
        return;
    _currentRound = currentRound;
    emit currentRoundChanged();
}

void QmlAdapter::setMaxRounds(QString maxRounds)
{
    if (maxRounds == _maxRounds)
        return;
    _maxRounds = maxRounds;
    if(_playerId == 0)
        lobbySettingsChanged();
    emit maxRoundsChanged();
}

void QmlAdapter::setView(QString view)
{
    if (view == _view)
        return;
    _view = view;
    emit viewChanged();
}

void QmlAdapter::setPlayerName(QString playerName)
{
    if (playerName == _playerName)
        return;
    _playerName = playerName;
    emit playerNameChanged();
}

void QmlAdapter::setPoints(int points)
{
    if (points == _points)
        return;
    _points = points;
    emit pointsChanged();
}

void QmlAdapter::setActiveOverviewItem(int activeOverviewItem)
{
    if (activeOverviewItem == _activeOverviewItem)
        return;
    _activeOverviewItem = activeOverviewItem;
    emit activeOverviewItemChanged();
}

void QmlAdapter::setPlayerCount(int playerCount)
{
    if (playerCount == _playerCount)
        return;
    _playerCount = playerCount;
    emit playerCountChanged();
}

void QmlAdapter::setPlayerId(int playerId)
{
    if (playerId == _playerId)
        return;
    _playerId = playerId;
    emit playerIdChanged();
}

void QmlAdapter::setTimeLeft(QString timeLeft)
{
    if (timeLeft == _timeLeft)
        return;
    _timeLeft = timeLeft;
    emit timeLeftChanged();
}

#define slotFunctionsEnd }
// ------------------------------------------ slots ------------------------------------------
#define slotFunctions {

QString QmlAdapter::getCategoryName(int idx)
{
    return QString::fromUtf8(_categories[idx].c_str());
}

QString QmlAdapter::getAnswer(int playerID, int categoryIDX)
{
    return QString::fromUtf8(_answers[playerID][categoryIDX].c_str());
}

QString QmlAdapter::getPlayer(int idx)
{
    auto player = std::next(std::begin(_players), idx);
    return QString::fromUtf8(player->second.c_str());
}

bool QmlAdapter::getDecision(int categoryIDX, int answerIDX, int voterIDX)
{
    return _decisions[categoryIDX][answerIDX][voterIDX];
}

void QmlAdapter::setActiveItemIA(int idx)
{
    setActiveOverviewItem(idx);
}

void QmlAdapter::setDecision(int categoryIDX, int answerIDX, int voterIDX)
{
    _decisions[categoryIDX][answerIDX][voterIDX] = !_decisions[categoryIDX][answerIDX][voterIDX];
    emit activeOverviewItemChanged(); //<- intentional! forces redraw
}

void QmlAdapter::addAnswer(QString answer)
{
    _unhandledanswers.emplace_back(answer.toStdString());
}

void QmlAdapter::hostLobby()
{
    onHostLobby(_playerName.toStdString());
}

void QmlAdapter::joinLobby()
{
    onJoinLobby(_lobbyCode.toStdString(), _playerName.toStdString());
}

void QmlAdapter::lobbySettingsChanged()
{
    onLobbySettingsChanged(_customCategories.toStdString(), _roundTime.toStdString(), _maxRounds.toStdString());
}

void QmlAdapter::disconnect()
{
    _disconnectedByClient = true;
    onDisconnect();
}

void QmlAdapter::sendChatMessage(QString str)
{
    onChatMessage(_playerName.toStdString(), str.toStdString());
}

void QmlAdapter::triggerStateChange(int state)
{
    switch (state)
    {
        case 0:  { onState(STATE::MAINMENU          ); break; }
        case 1:  { onState(STATE::LOBBY             ); break; }
        case 2:  { onState(STATE::SETUPROUND        ); break; }
        case 3:  { onState(STATE::INGAME            ); break; }
        case 4:  { onState(STATE::ANSWERREQUEST     ); break; }
        case 5:  { onState(STATE::OVERVIEW          ); break; }
        case 6:  { onState(STATE::ROUNDOVER         ); break; }
        case 7:  { onState(STATE::FINALSCORES       ); break; }
        case 8:  { onState(STATE::NEWGAME           ); break; }
    }
}

void QmlAdapter::triggerStateRelatedSignal(STATE state)
{
    switch (state)
    {
    case STATE::ANSWERREQUEST: {emit answersRequest(); break;}
    case STATE::MAINMENU     : break;
    case STATE::LOBBY        : break;
    case STATE::SETUPROUND   : break;
    case STATE::INGAME       : break;
    case STATE::OVERVIEW     : break;
    case STATE::ROUNDOVER    : break;
    case STATE::FINALSCORES  : break;
    case STATE::NEWGAME      : break;
    }
}

void QmlAdapter::changeVoteState(int answerIDX)
{
    onChangeVoteState(_activeOverviewItem, answerIDX, _playerId);
}

void QmlAdapter::clearChat()
{
    _chatLog.clear();
}

void QmlAdapter::setScores(Scores scores)
{
    for (auto& score : scores)
    {
        _finalScores_placements.push_back(score.first);
        _finalScores_scores.push_back(score.second);
    }
}

void QmlAdapter::sendAnswers()
{
   onSendAnswers(_unhandledanswers);
   _unhandledanswers.clear();
}

QString QmlAdapter::GetViewFromState(STATE view)
{
    switch (view)
    {
        case STATE::MAINMENU :      return "MainMenu";
        case STATE::LOBBY :         return "Lobby";
        case STATE::SETUPROUND :    return "Lobby";
        case STATE::INGAME :        return "Input";
        case STATE::ANSWERREQUEST : return "Input";
        case STATE::OVERVIEW :      return "Overview";
        case STATE::ROUNDOVER :     return (getPlayerId() == 0) ? "Intervention" : "Waiting";
        case STATE::FINALSCORES :   return "FinalScores";
        case STATE::NEWGAME :       return "Lobby";
    }
    return "MainMenu";
}

void QmlAdapter::AddChatMessage(const QString &sender, const QString &text)
{
    QString output = (sender == _playerName) ? "Du" : sender;
    _chatLog = output + ": " + text + "\n" + _chatLog;
    emit chatLogChanged();
}

#define slotFunctionsEnd }
