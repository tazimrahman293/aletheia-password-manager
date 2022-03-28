// main.cpp
// Contains the main entrypoint for the TBD password manager project.
// Authors: <insert here>

#include <algorithm>
#include <string>
#include <vector>

#include <Storage.h>
#include <hydrogen.h>

#include "auth/Authenticator.h"
#include "network/HTTPServer.h"
#include "cli/CommandLine.h"
#include "cli/InputParser.h"


Authenticator *auth = nullptr;	// Authentication and Encryption entry point


/**
 * Manages passwords
 */
int main(int argc, char *argv[])
{
	auth = new Authenticator();

    CommandLine cli(argc, argv, nullptr);

    // Set database filename (either using -d value or default to db.sqlite3)
    std::string dbFilename;
    if (cli.InputExists("-d"))
        dbFilename = cli.GetOption("-d");
    else
        dbFilename = "db.sqlite3";
    // Instantiate storage with filename
    Storage database(dbFilename);

    // Start in Server mode if -S given (no stdin, request come through HTTP)
    if (cli.InputExists("-S")) {

        // Host address/name (from -H value, defaults to 0.0.0.0)
        std::string hostAddress = "0.0.0.0";
        if (cli.InputExists("-H"))
            hostAddress = cli.GetOption("-H");

        // Host port (from -P value, defaults to 8089)
        int hostPort = 8089;
        if (cli.InputExists("-P"))
            hostPort = std::stoi(cli.GetOption("-P"));

        // Spin up server instance and run listen loop
        HTTPServer server(hostAddress, hostPort);
        server.Init(&database);
        server.Run(false);  // quiet = false
    } else {
        cli.SetDatabase(&database); // Use initialized database
        cli.HandleCommands();
    }

    return 0;

}
