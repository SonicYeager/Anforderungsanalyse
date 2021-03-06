#pragma once
#include "RandomGenerator.h"
#include <random>
#include <map>
#include <algorithm>
#include <set>

Letter RandomGenerator::GenerateLetter()	//could also use range of char (ascii-code)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 26);

	std::map<int, Letter> alphabet
	{
		{1, {'A'}},
		{2, {'B'}},
		{3, {'C'}},
		{4, {'D'}},
		{5, {'E'}},
		{6, {'F'}},
		{7, {'G'}},
		{8, {'H'}},
		{9, {'I'}},
		{10, {'J'}},
		{11, {'K'}},
		{12, {'L'}},
		{13, {'M'}},
		{14, {'N'}},
		{15, {'O'}},
		{16, {'P'}},
		{17, {'Q'}},
		{18, {'R'}},
		{19, {'S'}},
		{20, {'T'}},
		{21, {'U'}},
		{22, {'V'}},
		{23, {'W'}},
		{24, {'X'}},
		{25, {'Y'}},
		{26, {'Z'}}
	};

	return alphabet[distr(gen)];
}

Letter RandomGenerator::GenerateUnusedLetter(const Letters& filter)
{
	std::set<Letter> alphabet
	{
		{'A'},
		{'B'},
		{'C'},
		{'D'},
		{'E'},
		{'F'},
		{'G'},
		{'H'},
		{'I'},
		{'J'},
		{'K'},
		{'L'},
		{'M'},
		{'N'},
		{'O'},
		{'P'},
		{'Q'},
		{'R'},
		{'S'},
		{'T'},
		{'U'},
		{'V'},
		{'W'},
		{'X'},
		{'Y'},
		{'Z'}
	};

	for (const auto& elem : filter)
		alphabet.erase(elem);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, alphabet.size()-1);

	return *std::next(alphabet.begin(), distr(gen));
}
