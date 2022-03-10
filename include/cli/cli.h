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
#include "include/Storage.h"
#include "include/cli/InputParser.h"

#ifndef CLI_COMMANDHANDLER_H
#define CLI_COMMANDHANDLER_H
class cli : public InputParser{
    cli(int &argc, char **argv);

private:
    std::string input;
    std::string output = "";
    std::string command;
//
//    void HandleLogin(LoginAttemptEvent *event);
//    void HandleRegistration(AccountCreateEvent *event);
//    void HandleUpdatingAccount(AccountUpdateEvent *event);


public:

    virtual void HandleCommand() = 0; // Handling of every Event and Command

    // Grabbing and updating respective variables
    std::string GetInput() const;
    std::string GetCommand() const;
    std::string GetOutput();
    void ClearOutput();
    void updateOutput(const std::string& Output);
    virtual void printOutput() = 0;

};
#endif //CLI_COMMANDHANDLER_H
