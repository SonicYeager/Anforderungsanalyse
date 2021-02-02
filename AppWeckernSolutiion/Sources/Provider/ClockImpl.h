#pragma once
#include "Clock.h"

namespace Wecker
{
	class ClockImpl : public Clock
	{
	public:
		void Start() override;
		void Stop() override;

	private:
		bool m_run = false;
	};
} // namespace Wecker
