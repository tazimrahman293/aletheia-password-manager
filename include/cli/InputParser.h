//
// Created by Tazim on 2022-03-10.
//

#include <string>
#include <vector>
#include "Storage.h"

#ifndef INPUTPARSER_H
#define INPUTPARSER_H

class InputParser{

    std::vector <std::string> inputTokens;

public:
    InputParser(int argc, char **argv);

    int CountTokens() { return (int)inputTokens.size(); }
    const std::string& GetOption(const std::string &command);
    bool InputExists(const std::string &command);
    bool IsTokenAtPosition(const std::string &input, int position) { return inputTokens.at(position) == input; }
    const std::string& GetTokenAtPosition(int position);
};
#endif //INPUTPARSER_H
