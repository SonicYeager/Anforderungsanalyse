#ifndef QMLADAPTER_H
#define QMLADAPTER_H

#endif // QMLADAPTER_H
#include <QObject>
#include <vector>
#include <string>
#include <QAbstractListModel>
#include "UI.h"

using Categories = std::vector<std::string>;

class QmlAdapter : public QObject, public UI
{
    Q_OBJECT
    Q_PROPERTY(QString letter         READ getLetter          WRITE setLetter        NOTIFY letterChanged)
    Q_PROPERTY(Categories categories  READ getCategories      WRITE setCategories    NOTIFY categoriesChanged)
    Q_PROPERTY(int categoryCount      READ getCategoryCount   WRITE setCategoryCount NOTIFY categoryCountChanged)
    Q_PROPERTY(int currentRound       READ getCurrentRound    WRITE setCurrentRound  NOTIFY currentRoundChanged)
    Q_PROPERTY(int maxRounds          READ getMaxRounds       WRITE setMaxRounds     NOTIFY maxRoundsChanged)
    Q_PROPERTY(int points             READ getPoints          WRITE setPoints        NOTIFY pointsChanged)
    Q_PROPERTY(int timeLeft           READ getTimeLeft        WRITE setTimeLeft      NOTIFY timeLeftChanged)
    Q_PROPERTY(QString lobbyCode      READ getLobbyCode       WRITE setLobbyCode     NOTIFY lobbyCodeChanged)
public:
    explicit QmlAdapter(QObject *parent = nullptr);

    QString getLetter();
    QString getLobbyCode();
    Categories getCategories();
    int getCategoryCount();
    int getCurrentRound();
    int getMaxRounds();
    int getPoints();
    int getTimeLeft();

    void setLetter(QString letter);
    void setLobbyCode(QString lobbyCode);
    void setCategories(Categories categories);
    void setCategoryCount(int categoryCount);
    void setCurrentRound(int currentRound);
    void setMaxRounds(int maxRounds);
    void setPoints(int points);
    void setTimeLeft(int timeLeft);

    void Init(const GameStats&, const PlayerStats&) override;

public slots:
    QString getCategoryName(int idx);
signals:
    void letterChanged();
    void categoriesChanged();
    void categoryCountChanged();
    void currentRoundChanged();
    void maxRoundsChanged();
    void pointsChanged();
    void timeLeftChanged();
    void lobbyCodeChanged();

private:
    QString _letter = "C";
    QString _lobbyCode = "0000";
    int _categoryCount = 3;
    int _currentRound = 0;
    int _maxRounds = 5;
    int _points = 999;
    int _timeLeft = 0;
    Categories _categories = {"Stadt", "Land", "Fluss"};
    Categories _categories2 = {"Stadt", "Land", "Fluss", "Name", "Tier", "Beruf"};
};
