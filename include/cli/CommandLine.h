//
// Created by Tazim Rahman on 2022-02-28.
//
#ifndef CLI_COMMANDHANDLER_H
#define CLI_COMMANDHANDLER_H

#include <iostream>
#include <vector>


#include "auth/Authenticator.h"
#include "data/Account.h"
#include "network/EventBus.h"
#include "events/LoginAttemptEvent.h"
#include "network/HTTPServer.h"
#include "events/AccountCreateEvent.h"
#include "events/AccountUpdateEvent.h"
#include "Storage.h"
#include "cli/InputParser.h"
#include "cli/ContextManager.h"


class CommandLine : public InputParser {

    Storage* database;

    Authenticator *auth;

    ContextManager ctxManager;

    bool testMode;

    class CommandInStream : public std::istringstream {
    public:
        CommandInStream() = default;
    };
    class CommandOutStream : public std::ostringstream {
    public:
        CommandOutStream() = default;
    };

public:

    CommandLine(int argc, char **argv, Storage *db, bool testMode) :
            InputParser(argc, argv), database(db), testMode(testMode) { }
    CommandLine(int argc, char **argv, Storage *db) : CommandLine(argc, argv, db, false) { }

    CommandInStream inStream;
    CommandOutStream outStream;

    void Print(const std::string &message);
    void PrintLine(const std::string &message);
    std::string GetInput(const std::string &prompt);

    [[nodiscard]] bool IsRunning() const { return !ctxManager.quitting; }

    void HandleCommands(const std::string &command);

    void DoRegister(
            const std::string &username,
            const std::string &firstName,
            const std::string &lastName,
            const std::string &password
            );
    void DoLogin(const std::string &username, const std::string &password);

    void Init(Storage *db, Authenticator *authenticator) { this->database = db; this->auth = authenticator; };

};

#endif //CLI_COMMANDHANDLER_H
