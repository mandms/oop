#include <optional>
#include <string>
#include "MiniDictionary.cpp"

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc < 2)
    {
        return std::nullopt;
    }
    Args args;
    args.dictionaryFileName = argv[1];

    return args;
}

TExpressions SplitExpressions(std::string data, std::string delimiter)
{
    TExpressions expressions;
    size_t pos = 0;
    std::string token;

    while ((pos = data.find(delimiter)) != std::string::npos) {
        token = data.substr(0, pos);
        expressions.push_back(token);
        data.erase(0, pos + 1);
    }
    return expressions;
}

bool ParseFile(std::string fileName, TDictionary& dictionary)
{
    std::ifstream input;
    input.open(fileName);
    if (!input.is_open())
    {
        std::cout << OPEN_FILE_READING_ERROR << std::endl;
        return false;
    }

    std::string data;

    while (getline(input, data))
    {
        auto searchWordIdx = data.find(DICIONARY_DELIMITER);
        std::string searchWord = data.substr(0, searchWordIdx);
        std::string translate = data.substr(searchWordIdx + 1, data.length());
        TExpressions expressions = SplitExpressions(translate, EXPRESSION_DELIMITER);
        dictionary[searchWord] = expressions;
    }

    return true;
}

void UnknownWord(std::string data, TDictionary& dictionary, bool& isChanged)
{
    std::cout << UNKNOWN_WORD_PROMPT << data << std::endl;
    std::string translate;
    std::cin.ignore();
    getline(std::cin, translate);
    if (translate.empty())
    {
        std::cout << WORD_IGNORED << data << std::endl;
        return;
    }
    dictionary[data] = TExpressions{ translate };
    std::cout << TRANSLATE_SAVED << data << translate << std::endl;
    isChanged = true;
    return;
}

std::string ExpressionsToString(TExpressions expressions)
{
    return std::accumulate(
        expressions.begin(),
        expressions.end(),
        std::string(),
        [](std::string str, std::string s)
        {
            return str.empty() ? s : str + EXPRESSION_DELIMITER + s;
        }
    );
}

void SaveData(std::optional<Args> args, TDictionary dictionary)
{
    std::cout << FILE_CHANGED_PROMPT << std::endl;
    std::string fileName = DEFAULT_FILE_NAME;
    char response;
    std::cin >> response;

    if (std::find(begin(EXIT_KEYS), end(EXIT_KEYS), response) == end(EXIT_KEYS))
    {
        return;
    }

    if (args)
    {
        fileName = args->dictionaryFileName;
    }
    std::ofstream output;
    output.open(fileName);

    if (!output.is_open()) {
        std::cout << OPEN_FILE_WRITING_ERROR << std::endl;
        exit(1);
        return;
    }

    for (const auto& [word, translate] : dictionary)
    {
        output
            << word
            << DICIONARY_DELIMITER
            << ExpressionsToString(translate)
            << EXPRESSION_DELIMITER
            << std::endl;
    }

    std::cout << CHANGES_SAVED << std::endl;
}