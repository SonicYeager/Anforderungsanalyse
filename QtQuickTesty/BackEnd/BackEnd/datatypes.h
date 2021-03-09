#pragma once
#include <functional>
#include <string>
#include <vector>

template<typename ... Args>
using Event = std::function<void(Args...)>;

using ByteStream = std::vector<char>;
using LobbyCode = std::string;