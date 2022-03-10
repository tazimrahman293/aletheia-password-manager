//
// Created by Tazim Rahman on 2022-03-10.
//
#include <algorithm>
#include <string>
#include <vector>

#include "cli/InputParser.h"

InputParser::InputParser(int argc, char **argv) {
    for (int i = 1; i < argc; ++i)
        inputTokens.emplace_back(std::string(argv[i]));
}

bool InputParser::CommandExists(const std::string& command) const {
    return std::find(inputTokens.begin(), inputTokens.end(), command) != inputTokens.end();
}

const std::string& InputParser::GetOption(const std::string& command) const {
    std::vector<std::string>::const_iterator inputIterator;
    inputIterator = std::find(inputTokens.begin(), inputTokens.end(), command);
    if (inputIterator != inputTokens.end() && ++inputIterator != inputTokens.end())
        return *inputIterator;
    static const std::string empty_str;
    return empty_str;
}