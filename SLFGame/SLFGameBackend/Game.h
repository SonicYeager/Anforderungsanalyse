#include "GameLogic.h"

class Game : public GameLogic
{
public:
	int CalculatePoints(const std::vector<DECISION>&) override;
	void CheckGameFinished(GameStats&) override;
};