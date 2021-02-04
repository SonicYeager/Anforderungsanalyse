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
    Q_PROPERTY(QString letter           READ getLetter          WRITE setLetter        NOTIFY letterChanged)
    Q_PROPERTY(Categories categories           READ getCategories          WRITE setCategories        NOTIFY categoriesChanged)
    Q_PROPERTY(int categoryCount           READ getCategoryCount          WRITE setCategoryCount        NOTIFY categoryCountChanged)
    //Q_PROPERTY(QString currentRound     READ getCurrentRound    WRITE setcurrentRound  NOTIFY currentRoundChanged)
    //Q_PROPERTY(QString maxRounds        READ getMaxRounds       WRITE setMaxRounds     NOTIFY maxRoundsChanged)
    //Q_PROPERTY(QString points           READ getPoints          WRITE setPoints        NOTIFY pointsChanged)
public:
    explicit QmlAdapter(QObject *parent = nullptr);

    QString getLetter();
    Categories getCategories();
    int getCategoryCount();

    void setLetter(QString letter);
    void setCategories(Categories categories);
    void setCategoryCount(int categoryCount);

    void Init(const GameStats&, const PlayerStats&) override;

public slots:
    QString getCategoryName(int idx);
signals:
    void letterChanged();
    void categoriesChanged();
    void categoryCountChanged();

private:
    QString _letter = "C";
    int _categoryCount = 3;
    int _currentRound = 0;
    Categories _categories = {"Stadt", "Land", "Fluss"};
    Categories _categories2 = {"Stadt", "Land", "Fluss", "Name", "Tier", "Beruf"};
};
