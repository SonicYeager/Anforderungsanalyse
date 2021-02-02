#pragma once

namespace Wecker
{
	class SoundPlayer
	{
	public:
		virtual void Play() = 0;
		virtual void Stop() = 0;

		virtual ~SoundPlayer() = default;
	};
} // namespace Wecker
