#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "lab1.h"
#include <vector>

struct Args
{
    std::vector<std::string> inputFileNames;
    std::string outnputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: join.exe <input file1> ... <input file N> <output file>\n";
        return std::nullopt;
    }
    Args args;
    for (int i = 1; i < argc - 1; i++)
    {
        args.inputFileNames.push_back(argv[i]);
    }
    args.outnputFileName = argv[argc - 1];

    return args;
}

void JoinStreams(std::ifstream& input, std::ofstream& output)
{
    char ch;
    while (input.get(ch))
    {
        if (!output.put(ch))
        {
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args) 
    {
        return 1;
    }

    std::ofstream output;
    output.open(args->outnputFileName);

    if (!output.is_open()) {
        std::cout << "Failed to open '" << args->outnputFileName << "' for writing\n";
        return 1;
    }

    for (std::string inputFileName : args->inputFileNames)
    {
        std::ifstream input;
        input.open(inputFileName); //через -> обращаемся к значению в optional, через . обращаемся к optional

        if (!input.is_open())
        {
            std::cout << "Failed to open '" << inputFileName << "' for reading\n";
            return 1;
        }
        JoinStreams(input, output);

        if (input.bad())
        {
            std::cout << "Reading input file ['" << inputFileName << "'] error\n";
            return 1;
        }
    }
    
    //закрывать файлы не надо, т.к. при выходе из блока где была объявлена переменная, вызывается деструктор, который заботится об этом

    if (!output.flush())
    {
        std::cout << "Writing output file error\n";
        return 1;
    }

    return 0;
}
