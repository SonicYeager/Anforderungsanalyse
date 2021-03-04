#include "GameStatsSerializer.h"
#include <algorithm>

void GameStatsSerializer::Serialize(Messages::Message msg, NetworkData data)
{
	std::visit([&](auto&& type) {Serialize_impl(type, data); }, msg);
}

void GameStatsSerializer::Deserialize(Messages::Message msg, std::vector<char> data)
{
	std::visit([&](auto&& type) {Deserialize_impl(type, data); }, msg);
}

void GameStatsSerializer::Serialize_impl(Messages::HandleGameStats msg, NetworkData data)
{
	QByteArray serialized{};
	QDataStream serialzer{ &serialized, QIODevice::WriteOnly };
	serialzer.setByteOrder(QDataStream::BigEndian);
	serialzer.setVersion(QDataStream::Qt_5_15);

	serialzer << data.header;
	serialzer << data.currentLetter;
	serialzer << data.potentialId;
	serialzer << data.maxRounds;
	QString timeout{ data.timeout.c_str() };
	serialzer << timeout;
	QVector<qint8> points{};
	std::for_each(std::begin(data.points), std::end(data.points), [&points](const int& point) {points.push_back(point); });
	serialzer << points;
	QVector<QString> categories{};
	std::for_each(std::begin(data.categories), std::end(data.categories), [&categories](const std::string& str) {categories.push_back(str.c_str()); });
	serialzer << categories;
	QVector<QString> names{};
	std::for_each(std::begin(data.playerNames), std::end(data.playerNames), [&names](const std::string& str) {names.push_back(str.c_str()); });
	serialzer << names;
	QVector<QVector<DECISION>> decisions{};
	std::for_each(std::begin(data.decisions), std::end(data.decisions), [&decisions](const std::vector<DECISION>& decs)
		{
			QVector<DECISION> decis{};
			std::for_each(std::begin(decs), std::end(decs), [&decis](const DECISION& dec) {decis.push_back(dec); });
			decisions.push_back(decis);
		}
	);
	serialzer << decisions;
	QVector<QVector<QString>> answers{};
	std::for_each(std::begin(data.answers), std::end(data.answers), [&answers](const std::vector<std::string>& vstr)
		{
			QVector<QString> answ;
			std::for_each(std::begin(vstr), std::end(vstr), [&answ](const std::string& str) {answ.push_back(QString(str.c_str())); });
			answers.push_back(answ);
		}
	);
	serialzer << answers;
	std::vector<char> result;
	result.reserve(serialized.size());
	result = std::vector<char>(std::begin(serialized), std::end(serialized));
}


void GameStatsSerializer::Deserialize_impl(Messages::HandleGameStats msg, std::vector<char> data)
{
	QByteArray sdat;
	sdat.reserve(data.size());
	sdat = QByteArray(data.data(), data.size());
	QDataStream deserializer{ &sdat, QIODevice::ReadOnly };
	NetworkData deserialized{};
	deserializer.setByteOrder(QDataStream::BigEndian);
	deserializer.setVersion(QDataStream::Qt_5_15);

	deserializer >> deserialized.header;
	deserializer >> deserialized.currentLetter;
	deserializer >> deserialized.potentialId;
	deserializer >> deserialized.maxRounds;
	QString timeout{};
	deserializer >> timeout;
	deserialized.timeout = timeout.toStdString();
	QVector<qint8> points{};
	deserializer >> points;
	for (const int& point : points)
		deserialized.points.push_back(point);
	QVector<QString> categories{};
	deserializer >> categories;
	for (const QString& str : categories)
		deserialized.categories.push_back(str.toStdString());
	QVector<QString> names{};
	deserializer >> names;
	for (const QString& str : names)
		deserialized.playerNames.push_back(str.toStdString());
	QVector<QVector<DECISION>> decisions{};
	deserializer >> decisions;
	for (const QVector<DECISION>& decs : decisions)
	{
		std::vector<DECISION> decis{};
		for (const DECISION& dec : decs)
			decis.push_back(dec);
		deserialized.decisions.push_back(decis);
	}
	QVector<QVector<QString>> answers{};
	deserializer >> answers;
	for (const QVector<QString>& vstr : answers)
	{
		std::vector<std::string> answ;
		for (const QString& str : vstr)
			answ.push_back(str.toStdString());
		deserialized.answers.push_back(answ);
	}
}

void GameStatsSerializer::Serialize_impl(Messages::Alternative msg, NetworkData data)
{
}
void GameStatsSerializer::Deserialize_impl(Messages::Alternative msg, std::vector<char> data)
{
}
