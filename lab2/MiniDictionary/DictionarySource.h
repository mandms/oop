#include <optional>
#pragma once

typedef std::vector<std::string> TExpressions;
typedef std::map<std::string, TExpressions> TDictionary;

struct Args
{
    std::string dictionaryFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
TExpressions SplitExpressions(std::string data, std::string delimiter);
bool ParseFile(std::string fileName, TDictionary& dictionary);
void UnknownWord(std::string data, TDictionary& dictionary, bool& isChanged);
std::string ExpressionsToString(TExpressions expressions);
void SaveData(std::optional<Args> args, TDictionary dictionary);