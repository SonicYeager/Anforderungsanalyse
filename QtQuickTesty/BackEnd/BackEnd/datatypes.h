#pragma once
#include <functional>
#include <string>
#include <vector>
#include <map>

template<typename ... Args>
using Event = std::function<void(Args...)>;

using ByteStream = std::vector<char>;
using LobbyCode = std::string;

const int PORT = 4242;
const int HEADERSIZE = sizeof(int);