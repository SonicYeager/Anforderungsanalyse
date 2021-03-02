#pragma once
#include "QDataSerializer.h"
#include <algorithm>

QByteArray QDataSerializer::Serialize(const NetworkData& data)
{
	QByteArray serialized{};
	QDataStream serialzier{ &serialized, QIODevice::WriteOnly};
	serialzier.setByteOrder(QDataStream::BigEndian);
	serialzier.setVersion(QDataStream::Qt_5_15);
	
	serialzier << data.header;
	serialzier << data.currentLetter;
	serialzier << data.potentialId;
	serialzier << data.maxRounds;
	QString timeout{data.timeout.c_str()};
	serialzier << timeout;
	QVector<qint8> points{};
	std::for_each(std::begin(data.points), std::end(data.points), [&points](const int& point) {points.push_back(point); });
	serialzier << points;
	QVector<QString> categories{};
	std::for_each(std::begin(data.categories), std::end(data.categories), [&categories](const std::string& str) {categories.push_back(str.c_str()); });
	serialzier << categories;
	QVector<QString> names{};
	std::for_each(std::begin(data.playerNames), std::end(data.playerNames), [&names](const std::string& str) {names.push_back(str.c_str()); });
	serialzier << names;
	QVector<QVector<DECISION>> decisions{};
	std::for_each(std::begin(data.decisions), std::end(data.decisions), [&decisions](const std::vector<DECISION>& decs)
		{
			QVector<DECISION> decis{};
			std::for_each(std::begin(decs), std::end(decs), [&decis](const DECISION& dec) {decis.push_back(dec); });
			decisions.push_back(decis);
		}
	);
	serialzier << decisions;
	QVector<QVector<QString>> answers{};
	std::for_each(std::begin(data.answers), std::end(data.answers), [&answers](const std::vector<std::string>& vstr)
		{
			QVector<QString> answ;
			std::for_each(std::begin(vstr), std::end(vstr), [&answ](const std::string& str) {answ.push_back(QString(str.c_str())); });
			answers.push_back(answ);
		}
	);
	serialzier << answers;

	return serialized;
}

NetworkData QDataSerializer::Deserialize(const QByteArray& data)
{
	QByteArray sdat{ data };
	QDataStream deserialzier{ &sdat, QIODevice::ReadOnly };
	NetworkData deserialzied{};
	deserialzier.setByteOrder(QDataStream::BigEndian);
	deserialzier.setVersion(QDataStream::Qt_5_15);

	deserialzier >> deserialzied.header;
	deserialzier >> deserialzied.currentLetter;
	deserialzier >> deserialzied.potentialId;
	deserialzier >> deserialzied.maxRounds;
	QString timeout{};
	deserialzier >> timeout;
	deserialzied.timeout = timeout.toStdString();
	QVector<qint8> points{};
	deserialzier >> points;
	for(const int& point : points)
		deserialzied.points.push_back(point);
	QVector<QString> categories{};
	deserialzier >> categories;
	for (const QString& str : categories)
		deserialzied.categories.push_back(str.toStdString());
	QVector<QString> names{};
	deserialzier >> names;
	for (const QString& str : names)
		deserialzied.playerNames.push_back(str.toStdString());
	QVector<QVector<DECISION>> decisions{};
	deserialzier >> decisions;
	for (const QVector<DECISION>& decs : decisions)
	{
		std::vector<DECISION> decis{};
		for (const DECISION& dec : decs)
			decis.push_back(dec);
		deserialzied.decisions.push_back(decis);
	}
	QVector<QVector<QString>> answers{};
	deserialzier >> answers;
	for (const QVector<QString>& vstr : answers)
	{
		std::vector<std::string> answ;
		for (const QString& str : vstr)
			answ.push_back(str.toStdString());
		deserialzied.answers.push_back(answ);
	}


	return deserialzied;
}
