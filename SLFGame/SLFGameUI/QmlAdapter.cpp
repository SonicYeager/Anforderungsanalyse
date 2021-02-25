#include "QmlAdapter.h"

QmlAdapter::QmlAdapter(QObject *parent) :
    QObject(parent)
{

}
// ------------------------------------------ initializer function ------------------------------------------

void QmlAdapter::Init(const GameStats & gs, const PlayerStats & ps)
{
    setLobbyCode(QString::fromLocal8Bit(gs.GetLobbyCode().c_str()));
}

void QmlAdapter::PrepareGame(const GameStats & gs, const PlayerStats & ps)
{
    _unhandledanswers = {};
    setCurrentRound(gs.GetCurrentRound());
    setLetter(QChar(gs.GetCurrentLetter().letter));
    setCategories(gs.GetCategories());
    setPoints(ps.GetPoints());
    setLobbyScreenVisible(false);
    setOverviewScreenVisible(false);
    setEntryScreenVisible(true);
}

void QmlAdapter::PrepareFinalScores(const GameStats & gs, const PlayerStats & ps)
{
    setPoints(ps.GetPoints());
    setOverviewScreenVisible(false);
    setFScoresScreenVisible(true);
}

void QmlAdapter::PrepareOverview(const GameStats & gs, const PlayerStats & ps)
{
    setAnswers(ps.GetAnswers());
    emit answersChanged();
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

StrVector QmlAdapter::getAnswers()
{
    return _answers;
}

bool QmlAdapter::getCustomChecked()
{
    return _customChecked;
}

bool QmlAdapter::getLobbyScreenVisible()
{
    return _lobbyScreenVisible;
}

bool QmlAdapter::getEntryScreenVisible()
{
    return _entryScreenVisible;
}

bool QmlAdapter::getOverviewScreenVisible()
{
    return _overviewScreenVisible;
}

bool QmlAdapter::getFScoresScreenVisible()
{
    return _fscoresScreenVisible;
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

QString QmlAdapter::getTimeLeft()
{
    return _timeLeft;
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

void QmlAdapter::setAnswers(StrVector answers)
{
    if (answers == _answers)
        return;
    _answers = answers;
    _decisions.clear();
    for (unsigned long long i = 0; i < _answers.size(); i++)
        _decisions.emplace_back(0);
    emit answersChanged();
    emit decisionsChanged();
}

void QmlAdapter::setCustomChecked(bool checked)
{
    if (checked == _customChecked)
        return;
    _customChecked = checked;
    emit customCheckedChanged();
}

void QmlAdapter::setLobbyScreenVisible(bool visibility)
{
    if (visibility == _lobbyScreenVisible)
        return;
    _lobbyScreenVisible = visibility;
    emit lobbyScreenVisibleChanged();
}

void QmlAdapter::setEntryScreenVisible(bool visibility)
{
    if (visibility == _entryScreenVisible)
        return;
    _entryScreenVisible = visibility;
    emit entryScreenVisibleChanged();
}

void QmlAdapter::setOverviewScreenVisible(bool visibility)
{
    if (visibility == _overviewScreenVisible)
        return;
    _overviewScreenVisible = visibility;
    emit overviewScreenVisibleChanged();
}

void QmlAdapter::setFScoresScreenVisible(bool visibility)
{
    if (visibility == _fscoresScreenVisible)
        return;
    _fscoresScreenVisible = visibility;
    emit fscoresScreenVisibleChanged();
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

QString QmlAdapter::getAnswer(int idx)
{
    return QString::fromUtf8(_answers[idx].c_str());
}

int QmlAdapter::getDecision(int idx)
{
    return _decisions[idx];
}

void QmlAdapter::setActiveItemIA(int idx)
{
    setActiveOverviewItem(idx);
}

void QmlAdapter::setDecision(int idx, int newVal)
{
    _decisions[idx] = newVal;
    emit decisionsChanged();
}

void QmlAdapter::prepareGame()
{
    onPrepareGame(_customCategories.toStdString(), _timeLeft.toStdString(), _maxRounds.toStdString());
}

void QmlAdapter::prepareOverview()
{
    onPrepareOverview(_unhandledanswers);
}

void QmlAdapter::prepareNextRound()
{
    onPrepareNextRound(_decisions);
}

void QmlAdapter::addAnswer(QString answer)
{
    _unhandledanswers.emplace_back(answer.toStdString());
}

#define slotFunctionsEnd }
