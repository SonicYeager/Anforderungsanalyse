#include "RomanConvert.h"
#include <algorithm>
#include <iterator>
#include <vector>

std::vector<char> DecomposeRoman(std::string);
std::vector<int> MapRomanToDecimal(std::vector<char>);
std::vector<int> ApplyRomanRules(std::vector<int>);
int SumDecimal(std::vector<int>);

std::vector<int> DecomposeDecimal(int);
std::vector<std::string> MapDecimalToRoman(std::vector<int>);
std::string FuseRoman(std::vector<std::string>);

std::string DecimalToRoman(int dec)
{
    auto decomposed = DecomposeDecimal(dec);
    auto mapped = MapDecimalToRoman(decomposed);
    return FuseRoman(mapped);
}

int RomanToDecimal(const std::string& rom)
{
    auto decomposed = DecomposeRoman(rom);
    auto mapped = MapRomanToDecimal(decomposed);
    auto applyed = ApplyRomanRules(mapped);
    return SumDecimal(applyed);
}

std::vector<char> DecomposeRoman(std::string rom)
{
    std::vector<char> decomposedRoman{};
    for (auto roman : rom) 
    {
        decomposedRoman.push_back(roman);
    }
    return decomposedRoman;
}

std::vector<int> MapRomanToDecimal(std::vector<char> chars)
{
    std::vector<int> mappedDecimal{};
    for (auto cha : chars) 
    {
        switch (cha)
        {
            case('I'):
                mappedDecimal.push_back(1);
                break;
            case('V'):
                mappedDecimal.push_back(5);
                break;
            case('X'):
                mappedDecimal.push_back(10);
                break;
            case('L'):
                mappedDecimal.push_back(50);
                break;
            case('C'):
                mappedDecimal.push_back(100);
                break;
            case('D'):
                mappedDecimal.push_back(500);
                break;
            case('M'):
                mappedDecimal.push_back(1000);
                break;
            default:
                break;
        }
    }
    return mappedDecimal;
}

std::vector<int> ApplyRomanRules(std::vector<int> decimals) 
{
    std::vector<int> applyed{};
    for (size_t i = 1; i <= decimals.size(); ++i) 
    {
        if (i == decimals.size())
            applyed.push_back(decimals[i - 1]);
        else 
        {
            if (decimals[i - 1] < decimals[i])
            {
                applyed.push_back(decimals[i] - decimals[i - 1]);
                ++i;
            }
            else
                applyed.push_back(decimals[i - 1]);
        }
    }
    return applyed;
}

int SumDecimal(std::vector<int> decimals)
{
    int sum{};
    for (auto dec : decimals)
    {
        sum += dec;
    }
    return sum;
}

std::vector<int> DecomposeDecimal(int dec)
{
    std::vector<int> decomposedDecimal{};
    std::vector<int> divider{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    for (auto div : divider)
    {
        int divided = 0;
        do 
        {
            divided = dec / div;
            if (divided > 0)
            {
                dec -= div;
                decomposedDecimal.push_back(div);
            }
        } while (divided > 0);
    }
    return decomposedDecimal;
}

std::vector<std::string> MapDecimalToRoman(std::vector<int> decimals)
{
    std::vector<std::string> mappedRoman{};
    for (auto dec : decimals)
    {
        switch (dec)
        {
        case(1):
            mappedRoman.push_back("I");
            break;
        case(4):
            mappedRoman.push_back("IV");
            break;
        case(5):
            mappedRoman.push_back("V");
            break;
        case(9):
            mappedRoman.push_back("IX");
            break;
        case(10):
            mappedRoman.push_back("X");
            break;
        case(40):
            mappedRoman.push_back("XL");
            break;
        case(50):
            mappedRoman.push_back("L");
            break;
        case(90):
            mappedRoman.push_back("XC");
            break;
        case(100):
            mappedRoman.push_back("C");
            break;
        case(400):
            mappedRoman.push_back("CD");
            break;
        case(500):
            mappedRoman.push_back("D");
            break;
        case(900):
            mappedRoman.push_back("CM");
            break;
        case(1000):
            mappedRoman.push_back("M");
            break;
        default:
            break;
        }
    }
    return mappedRoman;
}

std::string FuseRoman(std::vector<std::string> chars)
{
    std::string sum{};
    for (auto& cha : chars)
    {
        sum += cha;
    }
    return sum;
}
