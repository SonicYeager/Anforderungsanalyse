#ifndef QMLADAPTER_H
#define QMLADAPTER_H
#endif // QMLADAPTER_H

#include <QObject>
#include <QAbstractListModel>
#include <string>
#include "datatypes.h"

class QmlAdapter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString data              READ getData                WRITE setData                NOTIFY dataChanged)
    Q_PROPERTY(QString labelText         READ getLabelText           WRITE setLabelText           NOTIFY labelTextChanged)

public:
    explicit QmlAdapter(QObject *parent = nullptr);

    //any specific backendtrigger
    void LogConnection(const std::string&);

    //getter
    QString getData();
    QString getLabelText();

    //setter
    void setData(QString data);
    void setLabelText(QString text);

    //events
    Event<> onStartHost;
    Event<> onJoinHost;

public slots:

    //anything the ui asks for or triggers (interactions with backend process)
    void startHost();
    void joinHost();

signals:
    void dataChanged();
    void labelTextChanged();

private:
    QString _data = "";
    QString _labelText = "Logs:\n";
};
