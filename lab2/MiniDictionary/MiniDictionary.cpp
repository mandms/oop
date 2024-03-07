#include <iostream>
#include <fstream>
#include <map>
#include <optional>
#include <string>
#include <vector>
#include <numeric>
#include <Windows.h>
#include "DictionarySource.h"

const std::string EXPRESSION_DELIMITER = ", ";
const std::string DICIONARY_DELIMITER = ".";
const std::string EXIT_PROGRAM = "...";
const std::string CHANGES_SAVED = "Изменения сохранены. До свидания.";
const std::string UNKNOWN_WORD_PROMPT = "Неизвестное слово “{}”. Введите перевод или пустую строку для отказа.";
const std::string WORD_IGNORED = "Слово “{}” проигнорировано.";
const std::string TRANSLATE_SAVED = "Слово “{}” сохранено в словаре как “{}”.";
const std::string DEFAULT_FILE_NAME = "dictionary.txt";
const std::string FILE_CHANGED_PROMPT = "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.";
const std::string OPEN_FILE_READING_ERROR = "Failed to open {} for reading.";
const std::string OPEN_FILE_WRITING_ERROR = "Failed to open {} for writing.";
const std::vector<char> EXIT_KEYS{ 'y', 'Y' };

void SetLayout()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
}

int main(int argc, char* argv[])
{
    SetLayout();

    auto args = ParseArgs(argc, argv);

    TDictionary dictionary;

    if (args && !ParseFile(args->dictionaryFileName, dictionary))
    {
        return 1;
    }

    std::string data;
    bool isChanged = false;

    while (std::cin >> data)
    {
        if (data == EXIT_PROGRAM)
        {
            if (isChanged)
            {
                SaveData(args, dictionary);
            }
            break;
        }

        if (!dictionary.count(data)) {
            UnknownWord(data, dictionary, isChanged);
            continue;
        }

        TExpressions expressions = dictionary.at(data);

        if (!expressions.size())
        {
            UnknownWord(data, dictionary, isChanged);
            continue;
        }

        std::cout << ExpressionsToString(expressions) << std::endl;
    }

    return 0;
}
