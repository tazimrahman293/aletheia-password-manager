//
// Created by Tazim Rahman on 2022-03-10.
//
#include <string>
#include <vector>

#include "include/cli/InputParsher.h"

InputParser(int& argc, char **argv) {
    for (int i = 1; i < argc; ++i)
        InputTokens.emplace_back(std::string(argv[i]));
}

bool CommandExists(const std::string& Command) const {
    return std::find(InputTokens.begin(), InputTokens.end(), Command) != InputTokens.end();
}

const std::string& GetOption(const std::string& Command) const {
    std::vector<std::string>::const_iterator InputIterator;
    InputIterator = std::find(InputTokens.begin(), InputTokens.end(), Command);
    if (InputIterator != InputTokens.end() && ++InputIterator != InputTokensend())
        return *InputIterator;
    static const std::string empty_str;
    return empty_str;
}