// main.cpp
// Contains the main entrypoint for the TBD password manager project.
// Authors: <insert here>

#include <algorithm>
#include <string>
#include <vector>

#include <Storage.h>

#include "network/HTTPServer.h"
#include "network/EventBus.h"

EventBus *EventBus::bus = nullptr;

class InputParser {

    std::vector<std::string> tokens;

public:

    InputParser(int& argc, char **argv) {
        for (int i = 1; i < argc; ++i)
            tokens.emplace_back(std::string(argv[i]));
    }

    bool HasOption(const std::string& option) const {
        return std::find(tokens.begin(), tokens.end(), option) != tokens.end();
    }

    const std::string& GetOptionValue(const std::string& option) const {
        std::vector<std::string>::const_iterator it;
        it = std::find(tokens.begin(), tokens.end(), option);
        if (it != tokens.end() && ++it != tokens.end())
            return *it;
        static const std::string empty_str;
        return empty_str;
    }
};

/**
 * Manages passwords
 */
int main(int argc, char *argv[])
{
    InputParser cmdParser(argc, argv);

    std::string dbFilename;
    if (cmdParser.HasOption("-d"))
        dbFilename = cmdParser.GetOptionValue("-d");
    else
        dbFilename = "db.sqlite3";
    Storage database(dbFilename);

    User record;
    record.pk = -1;
    record.firstName = "Jeremy";
    record.lastName = "Rempel";
    record.keyHash = "hunter2";
    record.typeID = User::UserType::Normal;
    database.InsertOrUpdate(record);
    std::cout << "Inserted/updated " << record.firstName << " (ID " << record.pk << ")" << std::endl;

    std::unique_ptr<User> pUser = database.GetByID<User>(record.pk);

    if (cmdParser.HasOption("-S")) {

        std::string hostAddress = "0.0.0.0";
        if (cmdParser.HasOption("-H"))
            hostAddress = cmdParser.GetOptionValue("-H");

        int hostPort = 8089;
        if (cmdParser.HasOption("-P"))
            hostPort = std::stoi(cmdParser.GetOptionValue("-P"));

        HTTPServer server(hostAddress, hostPort);
        server.Init();
        server.Run();
    }

    return 0;

}
