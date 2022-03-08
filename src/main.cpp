// main.cpp
// Contains the main entrypoint for the TBD password manager project.
// Authors: <insert here>

#include <algorithm>
#include <string>
#include <vector>

#include <Storage.h>

#include "network/HTTPServer.h"
#include "network/EventBus.h"

// IMPORTANT: Defines the EventBus static member `bus`
EventBus *EventBus::bus = nullptr;

/**
 * Gets flags/options/positional arguments from the command line using argc and argv)
 */
class InputParser {

    // All individual (space-delimited) tokens from the command-line input
    std::vector<std::string> tokens;

public:

    InputParser(int& argc, char **argv) {
        for (int i = 1; i < argc; ++i)
            tokens.emplace_back(std::string(argv[i]));
    }

    [[nodiscard]]
    bool HasOption(const std::string& option) const {
        return std::find(tokens.begin(), tokens.end(), option) != tokens.end();
    }

    [[nodiscard]]
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

    // Set database filename (either using -d value or default to db.sqlite3)
    std::string dbFilename;
    if (cmdParser.HasOption("-d"))
        dbFilename = cmdParser.GetOptionValue("-d");
    else
        dbFilename = "db.sqlite3";
    // Instantiate storage with filename
    Storage database(dbFilename);

    // Start in Server mode if -S given (no stdin, request come through HTTP)
    if (cmdParser.HasOption("-S")) {

        // Host address/name (from -H value, defaults to 0.0.0.0)
        std::string hostAddress = "0.0.0.0";
        if (cmdParser.HasOption("-H"))
            hostAddress = cmdParser.GetOptionValue("-H");

        // Host port (from -P value, defaults to 8089)
        int hostPort = 8089;
        if (cmdParser.HasOption("-P"))
            hostPort = std::stoi(cmdParser.GetOptionValue("-P"));

        // Spin up server instance and run listen loop
        HTTPServer server(hostAddress, hostPort);
        server.Init();
        server.Run();
    }

    return 0;

}
