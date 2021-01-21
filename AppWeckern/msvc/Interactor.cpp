#include "Interactor.h"
#include "TimeHandler.h"

std::string Interactor::InitApp()
{
	TimeHandler th{};
	return th.GetPresentTime();
}
