/**
 * cli.pp
 * Top level module containing implementations of handler functions for each user input
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>



#include "cli/CommandLine.h"
#include "cli/InputParser.h"
#include "network/EventBus.h"
#include "events/LoginAttemptEvent.h"
#include "Storage.h"
#include "network/HTTPServer.h"
#include "events/AccountCreateEvent.h"
#include "events/AccountUpdateEvent.h"
#include "Storage.h"


void CommandLine::HandleCommands() {
    //while (true) {
        std::cout << "CLI has been entered. Welcome!" << std::endl;
        if  (CountTokens() >= 5 && InputExists("login") && IsTokenAtPosition("login", 1)) {  // Login command

            std::cout << "Executing Login Command" << std::endl;

            // Storing user inputs
            std::string firstName = GetTokenAtPosition(2);
            std::string lastName = GetTokenAtPosition(3);
            // std::string Input_password = GetTokenAtPosition(4);

            std::vector<User> allUsers = database->GetAllUsers();

            for (User &user : allUsers) {
                if ((user.firstName == firstName) &&
                    (user.lastName == lastName)) {
                    // std::cout << "Login successful. Welcome " << *Database_ID->firstName <<" " << *Database_ID->lastName << std::endl;
                    std::cout << "Access to structure successful" << std::endl;
                    break;
                }
            }

            std::cout << "Login command finished being executed" << std::endl;

        } else if (InputExists("new-account") && IsTokenAtPosition("new-account", 1)) {  // Create account

            std::cout << "Registration command working" << std::endl;

        } else if (InputExists("edit-account") && IsTokenAtPosition("edit-account", 1)) {  // Edit account

            std::cout << "Updating account command working" << std::endl;

        }
    //}
}


