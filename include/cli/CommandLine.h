//
// Created by Tazim Rahman on 2022-02-28.
//
#include <string>
#include <vector>


#include "data/Account.h"
#include "network/EventBus.h"
#include "events/LoginAttemptEvent.h"
#include "network/HTTPServer.h"
#include "events/AccountCreateEvent.h"
#include "events/AccountUpdateEvent.h"
#include "Storage.h"
#include "cli/InputParser.h"

#ifndef CLI_COMMANDHANDLER_H
#define CLI_COMMANDHANDLER_H
class CommandLine : public InputParser {

    std::string input;
    std::string output;
    std::string command;

public:
    CommandLine(int argc, char **argv) : InputParser(argc, argv) { }

    void HandleCommand(); // Handling of every Event and Command

    // Grabbing and updating respective variables
    [[nodiscard]] std::string GetInput() const { return input; };
    [[nodiscard]] std::string GetCommand() const { return command; };
    [[nodiscard]] std::string GetOutput() const { return output; };
    void ClearOutput();
    void UpdateOutput(const std::string& Output);
    virtual void PrintOutput() = 0;

};
#endif //CLI_COMMANDHANDLER_H
