#pragma once
#include <variant>
#include "DataTypes.h"

namespace Messages
{
	enum class HEADER : int
	{
		PLAYER_NAME = 1,
		PLAYER_ID = 2,
		PLAYER_ANSWERS = 3,
		HANDLEGAMESETTINGS = 4,
		GAMESTATE = 5,
		CHATMESSAGE = 6,
		ALLANSWERS = 7,
		ROUNDSETUP = 8,
		ANSWERINDEX = 9,
		FINALSCORES = 10
	};

	struct HandleGameSettings	{ LobbySettings ls; };
	struct Playername			{ std::string playername; int id; }; 
	struct PlayerID				{ int id; };
	struct PlayerAnswers		{ std::vector<std::string> answers; int id; }; 
	struct GameState			{ STATE state; };
	struct ChatMessage			{ std::string sender; std::string text; }; 
	struct AllAnswers			{ std::vector<std::vector<std::string>> ans{}; };
	struct RoundSetup			{ RoundData data; };
	struct AnswerIndex			{ Index index; };
	struct FinalScores		    { Scores scores; };

	using Message = std::variant<Playername, PlayerID, HandleGameSettings, GameState, ChatMessage, PlayerAnswers, AllAnswers, RoundSetup, AnswerIndex, FinalScores>;

	inline HEADER GetMessageID(const Playername&) { return HEADER::PLAYER_NAME; };
	inline HEADER GetMessageID(const PlayerID&) { return HEADER::PLAYER_ID; };
	inline HEADER GetMessageID(const PlayerAnswers&) { return HEADER::PLAYER_ANSWERS; };
	inline HEADER GetMessageID(const HandleGameSettings&) { return HEADER::HANDLEGAMESETTINGS; };
	inline HEADER GetMessageID(const GameState&) { return HEADER::GAMESTATE; };
	inline HEADER GetMessageID(const ChatMessage&) { return HEADER::CHATMESSAGE; };
	inline HEADER GetMessageID(const AllAnswers&) { return HEADER::ALLANSWERS; };
	inline HEADER GetMessageID(const RoundSetup&) { return HEADER::ROUNDSETUP; };
	inline HEADER GetMessageID(const AnswerIndex&) { return HEADER::ANSWERINDEX; };
	inline HEADER GetMessageID(const FinalScores&) { return HEADER::FINALSCORES; };

	inline Message CreateMessage(HEADER header)
	{
		switch (header)
		{
		case HEADER::PLAYER_NAME: return Playername{};
		case HEADER::PLAYER_ID: return PlayerID{};
		case HEADER::PLAYER_ANSWERS: return PlayerAnswers{};
		case HEADER::HANDLEGAMESETTINGS: return HandleGameSettings{};
		case HEADER::GAMESTATE: return GameState{};
		case HEADER::CHATMESSAGE: return ChatMessage{};
		case HEADER::ALLANSWERS: return AllAnswers{};
		case HEADER::ROUNDSETUP: return RoundSetup{};
		case HEADER::ANSWERINDEX: return AnswerIndex{};
		case HEADER::FINALSCORES: return FinalScores{};
		}
		return HandleGameSettings{};
	};
	
}