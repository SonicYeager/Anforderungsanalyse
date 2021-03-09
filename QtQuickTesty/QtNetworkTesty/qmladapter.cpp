#include "qmladapter.h"

QmlAdapter::QmlAdapter(QObject *parent) : QObject(parent)
{}

void QmlAdapter::LogConnection(const std::string & logText)
{
    setLabelText(logText.c_str());
}

QString QmlAdapter::getData()
{
    return _data;
}

QString QmlAdapter::getLabelText()
{
    return _labelText;
}

void QmlAdapter::setData(QString data)
{
    _data = data;
    emit dataChanged();
}

void QmlAdapter::setLabelText(QString text)
{
    _labelText += "#" + QString::number(_msgNr) + "  " + text + "\n";
    _msgNr++;
    emit labelTextChanged();
}

void QmlAdapter::startHost()
{
    onStartServer();
}

void QmlAdapter::joinHost()
{
    onJoinServer();
}
