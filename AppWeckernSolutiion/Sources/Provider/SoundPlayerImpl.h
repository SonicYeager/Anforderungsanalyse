#pragma once
#include "SoundPlayer.h"

namespace Wecker
{
	class SoundPlayerImpl : public SoundPlayer
	{
	public:
		void Play() override;
		void Stop() override;
	};
} // namespace Wecker
