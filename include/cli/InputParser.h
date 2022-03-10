//
// Created by Tazim on 2022-03-10.
//

#include <string>
#include <vector>


#ifndef INPUTPARSER_H
#define INPUTPARSER_H

class InputParser{
private:
    std::vector <std::string> inputTokens;

public:
    InputParser(int argc, char **argv);
    const std::string& GetOption(const std::string &command) const;
    bool CommandExists(const std::string &command) const;
};
#endif //INPUTPARSER_H
