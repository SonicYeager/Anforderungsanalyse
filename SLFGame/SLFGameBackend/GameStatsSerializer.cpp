#pragma once
#include "slfgamebackendqt_global.h"
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
	QMap<int, QString> playerNames;
	std::for_each(std::begin(msg.ls.playerNames), std::end(msg.ls.playerNames), [&playerNames](const std::pair<int, std::string>& str) {playerNames.insert(str.first, str.second.c_str()); });
	data << catString;
	data << timeout;
	data << rounds;
	data << playerNames;
}

void GameStatsSerializer::Deserialize_impl(HandleGameSettings& msg, QDataStream& data)
{
	QString timeout{};
	QString catString{};
	QString rounds{};
	QMap<int, QString> playerNames;

	data >> catString;
	data >> timeout;
	data >> rounds;
	data >> playerNames;

	msg.ls.timeout = timeout.toStdString();
	msg.ls.categories = catString.toStdString();
	msg.ls.rounds = rounds.toStdString();
	auto qmKeys = playerNames.keys();
	for (size_t i{}; i < qmKeys.size(); ++i)
		msg.ls.playerNames.emplace(qmKeys[i], playerNames[qmKeys[i]].toStdString());

}

void GameStatsSerializer::Serialize_impl(const GameState& msg, QDataStream& data)
{
	data << msg.state;
}

void GameStatsSerializer::Deserialize_impl(GameState& msg, QDataStream& data)
{
	data >> msg.state;
}
