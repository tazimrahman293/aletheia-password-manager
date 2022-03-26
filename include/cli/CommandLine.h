//
// Created by Tazim Rahman on 2022-02-28.
//
#ifndef CLI_COMMANDHANDLER_H
#define CLI_COMMANDHANDLER_H

#include <vector>


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

    ContextManager ctxManager;

public:

    CommandLine(int argc, char **argv, Storage *db) : InputParser(argc, argv), database(db) { }

    static void Print(const std::string &message);
    static void PrintLine(const std::string &message);
    static std::string GetInput(const std::string &prompt);

    void HandleCommands();

    void SetDatabase(Storage* db) { this->database = db; };

};

#endif //CLI_COMMANDHANDLER_H
