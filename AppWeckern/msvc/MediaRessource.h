#pragma once
#include <filesystem>

class MediaRessource
{
public:
	virtual void PlayAudioFile(const std::filesystem::path&) = 0;
	virtual ~MediaRessource() = default;
};