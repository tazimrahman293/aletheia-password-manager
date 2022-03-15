//
// Created by Tazim on 2022-03-10.
//

#include <string>
#include <vector>
#include "Storage.h"

#ifndef INPUTPARSER_H
#define INPUTPARSER_H

class InputParser{


public:
    std::vector <std::string> inputTokens;
    InputParser(int argc, char **argv, Storage* Database);
    const std::string& GetOption(const std::string &command) const;
    bool InputExists(const std::string &command) const;
};
#endif //INPUTPARSER_H
