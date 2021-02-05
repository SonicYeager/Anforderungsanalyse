#include "QmlAdapter.h"

QmlAdapter::QmlAdapter(QObject *parent) :
    QObject(parent)
{

}
// ------------------------------------------ initializer function ------------------------------------------

void QmlAdapter::Init(const GameStats & gs, const PlayerStats & ps)
{
    setCurrentRound(gs.GetCurrentRound());
    setLetter(QChar(gs.GetCurrentLetter().letter));
}


// ------------------------------------------ getter ------------------------------------------

QString QmlAdapter::getLetter()
{
    return _letter;
}

Categories QmlAdapter::getCategories()
{
    return _categories;
}

int QmlAdapter::getCategoryCount()
{
    return _categoryCount;
}

int QmlAdapter::getCurrentRound()
{
    return _currentRound;
}

int QmlAdapter::getMaxRounds()
{
    return _maxRounds;
}

int QmlAdapter::getPoints()
{
    return _points;
}

int QmlAdapter::getTimeLeft()
{
    return _timeLeft;
}

// ------------------------------------------ setter ------------------------------------------

void QmlAdapter::setLetter(QString letter)
{
    if (letter == _letter)
        return;
    _letter = letter;
    emit letterChanged();
}

void QmlAdapter::setCategories(Categories categories)
{
    if (categories == _categories)
        return;
    _categories = categories;
    emit categoriesChanged();
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

void QmlAdapter::setMaxRounds(int maxRounds)
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

void QmlAdapter::setTimeLeft(int timeLeft)
{
    if (timeLeft == _timeLeft)
        return;
    _timeLeft = timeLeft;
    emit timeLeftChanged();
}


// ------------------------------------------ slots ------------------------------------------
QString QmlAdapter::getCategoryName(int idx)
{
    return QString::fromUtf8(_categories[idx].c_str());
}
