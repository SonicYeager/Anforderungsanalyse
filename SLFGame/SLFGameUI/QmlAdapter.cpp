#include "QmlAdapter.h"

QmlAdapter::QmlAdapter(QObject *parent) :
    QObject(parent)
{}
// ------------------------------------------ initializer function ------------------------------------------

void QmlAdapter::PrepareGame(const GameStats & gs)
{
    _unhandledanswers = {};
    setCurrentRound(gs.GetCurrentRound());
    setLetter(QChar(gs.GetCurrentLetter().letter));
    setCategories(gs.GetCategories());
    setPoints(gs.GetPlayerStats(_playerId).GetPoints());
    setView("Input");
}

void QmlAdapter::PrepareFinalScores(const GameStats & gs)
{
    setPoints(gs.GetPlayerStats(_playerId).GetPoints());
    setView("FinalScores");
}

void QmlAdapter::PrepareOverview(const GameStats & gs)
{
    addPlayerAnswers(gs);
    setView("Overview");
    emit answersChanged();
}

void QmlAdapter::PrepareLobby(const GameStats & gs)
{
    setLobbyCode(QString::fromLocal8Bit(gs.GetLobbyCode().c_str()));
    setView("Lobby");
}

void QmlAdapter::PlayerJoined(const GameStats & gs, int id)
{
    _players.push_back(gs.GetPlayerStats(id).GetPlayerName());
    setPlayerCount(_players.size());
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

StrVector QmlAdapter::getPlayers()
{
    return _players;
}

bool QmlAdapter::getCustomChecked()
{
    return _customChecked;
}

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
    emit customCategoriesChanged();
}

void QmlAdapter::setCategories(StrVector categories)
{
    if (categories == _categories)
        return;
    _categories = categories;
    _categoryCount = _categories.size();
    emit categoriesChanged();
    emit categoryCountChanged();
}

void QmlAdapter::setAnswers(StrVector2D answers)
{
    if (answers == _answers)
        return;
    _answers = answers;
    _decisions.clear();
    for (int i = 0; i < _playerCount; i++)
        _decisions.emplace_back();
    for (int i = 0; i < _categoryCount - 1; i++)
        _decisions[i].emplace_back(DECISION::UNANSWERED);

    emit answersChanged();
    emit decisionsChanged();
}

void QmlAdapter::setPlayers(StrVector players)
{
    if (players == _players)
        return;
    _players = players;
    emit playersChanged();
}

void QmlAdapter::setCustomChecked(bool checked)
{
    if (checked == _customChecked)
        return;
    _customChecked = checked;
    emit customCheckedChanged();
}

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
    _playerId = playerId;
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
    return QString::fromUtf8(_players[idx].c_str());
}

DECISION QmlAdapter::getDecision(int playerID, int categoryIDX)
{
    return _decisions[playerID][categoryIDX];
}

void QmlAdapter::setActiveItemIA(int idx)
{
    setActiveOverviewItem(idx);
}

void QmlAdapter::setDecision(int playerID, int categoryIDX, int newVal)
{
    auto dec = static_cast<DECISION>(newVal);
    _decisions[playerID][categoryIDX] = dec;
    emit decisionsChanged();
}

void QmlAdapter::prepareGame()
{
    onPrepareGame(_customCategories.toStdString(), _timeLeft.toStdString(), _maxRounds.toStdString());
}

void QmlAdapter::prepareOverview()
{
    onPrepareOverview(_unhandledanswers, _playerId);
}

void QmlAdapter::prepareNextRound()
{
    // CHANGE ME SOON ----------------------------------------------------------------------
    onPrepareNextRound(_decisions[0], _playerId);
}

void QmlAdapter::addAnswer(QString answer)
{
    _unhandledanswers.emplace_back(answer.toStdString());
}

void QmlAdapter::addPlayerAnswers(GameStats gs)
{
    StrVector2D result;
    for (int i = 0; i < gs.GetPlayerCount(); i++)
        result.push_back(gs.GetPlayerStats(i).GetAnswers());
    setAnswers(result);
}

void QmlAdapter::hostLobby()
{
    onHost(_playerName.toStdString());
}

void QmlAdapter::joinLobby(QString lobbyCode)
{
    onJoin(lobbyCode.toStdString(), _playerName.toStdString());
}

#define slotFunctionsEnd }
