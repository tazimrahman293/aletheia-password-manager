//
// Created by Tazim on 2022-03-10.
//

#include <string>
#include <vector>


#ifndef INPUTPARSER_H
#define INPUTPARSER_H

class InputParser{
private:
    std::vector <std::string> InputTokens;

public:
    const std::string& GetOption(const std::string &Command) const;
    bool CommandExists(const std::string &Command) const;
};
#endif //INPUTPARSER_H
