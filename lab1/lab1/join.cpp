#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "lab1.h"
#include <vector>

const std::string INVALID_ARGUMENTS_COUNT_ERROR = "Invalid arguments count\n"
    "Usage: join.exe <input file1> ... <input file N> <output file>\n";
const int MIN_ARGS_COUNT = 3;
const std::string OPEN_FILE_WRITING_ERROR = "Failed to open file for writing: ";
const std::string OPEN_FILE_READING_ERROR = "Failed to open file for reading: ";
const std::string INPUT_FILE_ERROR = "Reading input file error:";
const std::string WRITING_OUTPUT_ERROR = "Writing output file error\n";


struct Args
{
    std::vector<std::string> inputFileNames;
    std::string outnputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc < MIN_ARGS_COUNT)
    {
        std::cout << INVALID_ARGUMENTS_COUNT_ERROR;
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
    output.open(args->outnputFileName); //TODO std::ios::binary;

    if (!output.is_open()) {
        std::cout << OPEN_FILE_WRITING_ERROR << args->outnputFileName << std::endl;
        return 1;
    }

    for (std::string inputFileName : args->inputFileNames)
    {
        std::ifstream input;
        input.open(inputFileName); //через -> обращаемся к значению в optional, через . обращаемся к optional

        if (!input.is_open())
        {
            std::cout << OPEN_FILE_READING_ERROR << inputFileName << std::endl;
            return 1;
        }
        JoinStreams(input, output);

        if (input.bad())
        {
            std::cout << INPUT_FILE_ERROR << inputFileName << std::endl;
            return 1;
        }
    }
    
    //закрывать файлы не надо, т.к. при выходе из блока где была объявлена переменная, вызывается деструктор, который заботится об этом

    if (!output.flush())
    {
        std::cout << WRITING_OUTPUT_ERROR;
        return 1;
    }

    return 0;
}
