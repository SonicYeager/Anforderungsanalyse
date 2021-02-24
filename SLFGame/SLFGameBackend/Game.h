#include "GameLogic.h"

class Game : public GameLogic
{
public:
	int CalculatePoints(const std::vector<int>&) override;
	void CheckGameFinished(GameStats&) override;
};