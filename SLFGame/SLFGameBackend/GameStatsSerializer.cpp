#pragma once
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"
#include "GameStatsSerializer.h"
#include <algorithm>

std::vector<char> GameStatsSerializer::Serialize(const Message& msg)
{
	QByteArray serializedData{};
	QDataStream dataStream{ &serializedData, QIODevice::WriteOnly };
	dataStream.setVersion(QDataStream::Qt_5_15);
	
	dataStream << std::visit([&](auto&& type) {return Messages::GetMessageID(type); }, msg);

	std::visit([&](auto&& type) {Serialize_impl(type, dataStream); }, msg);

	return { std::begin(serializedData), std::end(serializedData) };
}

Message GameStatsSerializer::Deserialize(const std::vector<char>& data)
{
	QByteArray sdat;
	sdat.reserve(data.size());
	sdat = QByteArray(data.data(), data.size());
	QDataStream dataStream{ &sdat, QIODevice::ReadOnly };
	
	dataStream.setVersion(QDataStream::Qt_5_15);

	HEADER header;
	dataStream >> header;

	Message message{ CreateMessage(header) };

	std::visit([&](auto&& type) {Deserialize_impl(type, dataStream); }, message);
	return message;
}

void GameStatsSerializer::Serialize_impl(const HandleGameStats& msg, QDataStream& data)
{
	data << msg.gs.currentLetter;
	data << msg.gs.maxRounds;
	QString timeout{ msg.gs.timeout.c_str() };
	data << timeout;
	QVector<qint8> points{ std::begin(msg.gs.points), std::end(msg.gs.points) };
	//std::for_each(std::begin(msg.gs.points), std::end(msg.gs.points), [&points](const int& point) {points.push_back(point); });
	data << points;
	QStringList categories;
	std::for_each(std::begin(msg.gs.categories), std::end(msg.gs.categories), [&categories](const std::string& str) {categories.push_back(str.c_str()); });
	data << categories;
	QStringList names;
	std::for_each(std::begin(msg.gs.playerNames), std::end(msg.gs.playerNames), [&names](const std::string& str) {names.push_back(str.c_str()); });
	data << names;
	QVector<QVector<DECISION>> decisions;
	std::for_each(std::begin(msg.gs.decisions), std::end(msg.gs.decisions), [&decisions](const std::vector<DECISION>& decs)
		{
			QVector<DECISION> decis{};
			std::for_each(std::begin(decs), std::end(decs), [&decis](const DECISION& dec) {decis.push_back(dec); });
			decisions.push_back(decis);
		}
	);
	data << decisions;
	QVector<QVector<QString>> answers{};
	std::for_each(std::begin(msg.gs.answers), std::end(msg.gs.answers), [&answers](const std::vector<std::string>& vstr)
		{
			QVector<QString> answ;
			std::for_each(std::begin(vstr), std::end(vstr), [&answ](const std::string& str) {answ.push_back(QString(str.c_str())); });
			answers.push_back(answ);
		}
	);
	data << answers;
	data << msg.gs.state;
}

void GameStatsSerializer::Deserialize_impl(HandleGameStats& msg, QDataStream& data)
{
	data >> msg.gs.currentLetter;
	data >> msg.gs.maxRounds;
	QString timeout{};
	data >> timeout;
	msg.gs.timeout = timeout.toStdString();
	QVector<qint8> points{};
	data >> points;
	for (const int& point : points)
		msg.gs.points.push_back(point);
	QStringList categories{};
	data >> categories;
	for (const QString& str : categories)
		msg.gs.categories.push_back(str.toStdString());
	QStringList names{};
	data >> names;
	for (const QString& str : names)
		msg.gs.playerNames.push_back(str.toStdString());
	QVector<QVector<DECISION>> decisions{};
	data >> decisions;
	for (const QVector<DECISION>& decs : decisions)
	{
		std::vector<DECISION> decis{};
		for (const DECISION& dec : decs)
			decis.push_back(dec);
		msg.gs.decisions.push_back(decis);
	}
	QVector<QVector<QString>> answers{};
	data >> answers;
	for (const QVector<QString>& vstr : answers)
	{
		std::vector<std::string> answ;
		for (const QString& str : vstr)
			answ.push_back(str.toStdString());
		msg.gs.answers.push_back(answ);
	}
	data >> msg.gs.state;
}

void GameStatsSerializer::Serialize_impl(const Playername& msg, QDataStream& data)
{
	QString playername{ msg.playername.c_str() };
	data << playername;
}

void GameStatsSerializer::Deserialize_impl(Playername& msg, QDataStream& data)
{
	QString playername{};
	data >> playername;
	msg.playername = playername.toStdString();
}

void GameStatsSerializer::Serialize_impl(const PlayerID& msg, QDataStream& data)
{
	data << msg.id;
}

void GameStatsSerializer::Deserialize_impl(PlayerID& msg, QDataStream& data)
{
	data >> msg.id;
}

void GameStatsSerializer::Serialize_impl(const PlayerAnswers& msg, QDataStream& data)
{
	QStringList answers;
	std::for_each(std::begin(msg.answers), std::end(msg.answers), [&answers](const std::string& str) {answers.push_back(str.c_str()); });
	data << answers;
}

void GameStatsSerializer::Deserialize_impl(PlayerAnswers& msg, QDataStream& data)
{
	QStringList answers{};
	data >> answers;
	for (const QString& answer : answers)
		msg.answers.push_back(answer.toStdString());
}

void GameStatsSerializer::Serialize_impl(const HandleGameSettings& msg, QDataStream& data)
{
	QString timeout{msg.ls.timeout.c_str()};
	QString catString{ msg.ls.categories.c_str() };
	QString rounds{ msg.ls.rounds.c_str() };
	QStringList cats;
	std::for_each(std::begin(msg.ls.cats), std::end(msg.ls.cats), [&cats](const std::string& str) {cats.push_back(str.c_str()); });
	data << timeout;
	data << catString;
	data << rounds;
	data << msg.ls.maxRounds;
	data << cats;
}

void GameStatsSerializer::Deserialize_impl(HandleGameSettings& msg, QDataStream& data)
{
	QString timeout{};
	QString catString{};
	QString rounds{};
	QStringList cats;

	data >> timeout;
	data >> catString;
	data >> rounds;
	data >> msg.ls.maxRounds;
	data >> cats;

	msg.ls.timeout = timeout.toStdString();
	msg.ls.categories = catString.toStdString();
	msg.ls.rounds = rounds.toStdString();
	for (const QString& cat : cats)
		msg.ls.cats.push_back(cat.toStdString());
}
